/* Python extension interface code */

#include "Python.h"
#include "numpy/arrayobject.h"

static PyObject *Register_Histogram(PyObject *self, PyObject *args)
{
     /*
       joint histogram memory is created in python to avoid memory leak problem 
     */

    int num;
    int numM;
    int nd;
    int type;
    int itype;
    int nd_histo;
    int nd_rotmatrix;
    int nd_S;
    npy_intp *dimsF;
    npy_intp *dimsG;
    npy_intp *dims_histo;
    npy_intp *dims_rotmatrix;
    npy_intp *dims_S;
    unsigned char *imageG;
    unsigned char *imageF;
    double        *pHisto;
    double        *M;
    int           *S;
    PyObject *imgArray1 = NULL;
    PyObject *imgArray2 = NULL;
    PyObject *rotArray  = NULL;
    PyObject *SArray    = NULL;
    PyObject *hArray    = NULL;
	
    if(!PyArg_ParseTuple(args, "OOOOO", &imgArray1, &imgArray2, &rotArray, &SArray, &hArray))
	goto exit;

    /* check in the Python code that F and G are the same dims, type */
    imageF = (unsigned char *)PyArray_DATA(imgArray1);
    imageG = (unsigned char *)PyArray_DATA(imgArray2);
    nd     = PyArray_NDIM(imgArray1);
    /* reads dims as 0 = layers, 1 = rows, 2 = cols */
    dimsF  = PyArray_DIMS(imgArray1);
    dimsG  = PyArray_DIMS(imgArray2);
    type   = PyArray_TYPE(imgArray1);
    num    = PyArray_SIZE(imgArray1);

    M = (double *)PyArray_DATA(rotArray);
    nd_rotmatrix   = PyArray_NDIM(rotArray);
    dims_rotmatrix = PyArray_DIMS(rotArray);
    numM           = PyArray_SIZE(rotArray);

    S = (int *)PyArray_DATA(SArray);
    nd_S   = PyArray_NDIM(SArray);
    dims_S = PyArray_DIMS(SArray);

    pHisto = (double *)PyArray_DATA(hArray);
    nd_histo   = PyArray_NDIM(hArray);
    dims_histo = PyArray_DIMS(hArray);
    /* check to make sure this is 256x256  */

    if(!NI_Histogram2D((int)dimsF[0], (int)dimsF[1], (int)dimsF[2], 
                       (int)dimsG[0], (int)dimsG[1], (int)dimsG[2], 
		       S, M, imageG, imageF, pHisto))
	    goto exit;

exit:

    /* return the 2D histogram */
    return PyErr_Occurred() ? NULL : (PyObject*)Py_BuildValue(""); 

}


static PyObject *Register_HistogramLite(PyObject *self, PyObject *args)
{
     /*
       joint histogram memory is created in python to avoid memory leak problem 
     */

    int num;
    int nd;
    int type;
    int itype;
    int nd_histo;
    int nd_rotmatrix;
    int nd_S;
    npy_intp *dimsF;
    npy_intp *dimsG;
    npy_intp *dims_histo;
    npy_intp *dims_rotmatrix;
    npy_intp *dims_S;
    unsigned char *imageG;
    unsigned char *imageF;
    double        *pHisto;
    double        *M;
    int           *S;
    PyObject *imgArray1 = NULL;
    PyObject *imgArray2 = NULL;
    PyObject *rotArray  = NULL;
    PyObject *SArray    = NULL;
    PyObject *hArray    = NULL;
	
    if(!PyArg_ParseTuple(args, "OOOOO", &imgArray1, &imgArray2, &rotArray, &SArray, &hArray))
	goto exit;

    /* check in the Python code that F and G are the same dims, type */
    imageF = (unsigned char *)PyArray_DATA(imgArray1);
    imageG = (unsigned char *)PyArray_DATA(imgArray2);
    /* reads dims as 0 = layers, 1 = rows, 2 = cols */
    nd     = PyArray_NDIM(imgArray1);
    dimsF  = PyArray_DIMS(imgArray1);
    dimsG  = PyArray_DIMS(imgArray2);
    type   = PyArray_TYPE(imgArray1);
    num    = PyArray_SIZE(imgArray1);

    M = (double *)PyArray_DATA(rotArray);
    nd_rotmatrix   = PyArray_NDIM(rotArray);
    dims_rotmatrix = PyArray_DIMS(rotArray);

    S = (int *)PyArray_DATA(SArray);
    nd_S   = PyArray_NDIM(SArray);
    dims_S = PyArray_DIMS(SArray);

    pHisto = (double *)PyArray_DATA(hArray);
    nd_histo   = PyArray_NDIM(hArray);
    dims_histo = PyArray_DIMS(hArray);
    /* check to make sure this is 256x256  */

    if(!NI_Histogram2DLite((int)dimsF[0], (int)dimsF[1], (int)dimsF[2], 
                           (int)dimsG[0], (int)dimsG[1], (int)dimsG[2], 
		            S, M, imageG, imageF, pHisto))
	    goto exit;

exit:

    /* return the 2D histogram */
    return PyErr_Occurred() ? NULL : (PyObject*)Py_BuildValue(""); 

}

static PyObject *Register_LinearResample(PyObject *self, PyObject *args)
{

    int num;
    int nd;
    int type;
    int itype;
    int nd_rotmatrix;
    int nd_S;
    npy_intp *dimsF;
    npy_intp *dimsG;
    npy_intp *dims_rotmatrix;
    npy_intp *dims_S;
    unsigned char *imageG;
    unsigned char *imageF;
    double        *M;
    int           *S;
    PyObject *imgArray1 = NULL;
    PyObject *imgArray2 = NULL;
    PyObject *rotArray  = NULL;
    PyObject *SArray    = NULL;
	
    if(!PyArg_ParseTuple(args, "OOOO", &imgArray1, &imgArray2, &rotArray, &SArray))
	goto exit;

    /* check in the Python code that F and G are the same dims, type */
    imageF = (unsigned char *)PyArray_DATA(imgArray1);
    imageG = (unsigned char *)PyArray_DATA(imgArray2);
    /* reads dims as 0 = layers, 1 = rows, 2 = cols */
    nd     = PyArray_NDIM(imgArray1);
    dimsF  = PyArray_DIMS(imgArray1);
    dimsG  = PyArray_DIMS(imgArray2);
    type   = PyArray_TYPE(imgArray1);
    num    = PyArray_SIZE(imgArray1);

    M = (double *)PyArray_DATA(rotArray);
    nd_rotmatrix   = PyArray_NDIM(rotArray);
    dims_rotmatrix = PyArray_DIMS(rotArray);

    S = (int *)PyArray_DATA(SArray);
    nd_S   = PyArray_NDIM(SArray);
    dims_S = PyArray_DIMS(SArray);

    if(!NI_LinearResample((int)dimsF[0], (int)dimsF[1], (int)dimsF[2], 
                          (int)dimsG[0], (int)dimsG[1], (int)dimsG[2], 
		           S, M, imageG, imageF))
	    goto exit;

exit:

    return PyErr_Occurred() ? NULL : (PyObject*)Py_BuildValue(""); 

}

static PyMethodDef RegisterMethods[] =
{
    { "register_histogram",       Register_Histogram,      METH_VARARGS, NULL },
    { "register_histogram_lite",  Register_HistogramLite,  METH_VARARGS, NULL },
    { "register_linear_resample", Register_LinearResample, METH_VARARGS, NULL },
    {  NULL, NULL, 0, NULL},
};

void init_register(void)
{
    Py_InitModule("_register", RegisterMethods);
    import_array();
}


