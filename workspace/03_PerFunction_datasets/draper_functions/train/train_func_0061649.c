convert_to_double(PyObject **v, double *dbl)
{
    register PyObject *obj = *v;

    if (PyInt_Check(obj)) {
        *dbl = (double)PyInt_AS_LONG(obj);
    }
    else if (PyLong_Check(obj)) {
        *dbl = PyLong_AsDouble(obj);
        if (*dbl == -1.0 && PyErr_Occurred()) {
            *v = NULL;
            return -1;
        }
    }
    else {
        Py_INCREF(Py_NotImplemented);
        *v = Py_NotImplemented;
        return -1;
    }
    return 0;
}
