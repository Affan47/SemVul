_PyEval_SliceIndex(PyObject *v, Py_ssize_t *pi)
{
    if (v != NULL) {
        Py_ssize_t x;
        if (PyInt_Check(v)) {


            x = PyInt_AS_LONG(v);
        }
        else if (PyIndex_Check(v)) {
            x = PyNumber_AsSsize_t(v, NULL);
            if (x == -1 && PyErr_Occurred())
                return 0;
        }
        else {
            PyErr_SetString(PyExc_TypeError,
                            "slice indices must be integers or "
                            "None or have an __index__ method");
            return 0;
        }
        *pi = x;
    }
    return 1;
}
