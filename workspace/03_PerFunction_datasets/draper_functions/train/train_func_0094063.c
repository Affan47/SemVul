float_is_integer(PyObject *v)
{
    double x = PyFloat_AsDouble(v);
    PyObject *o;

    if (x == -1.0 && PyErr_Occurred())
        return NULL;
    if (!Py_IS_FINITE(x))
        Py_RETURN_FALSE;
    errno = 0;
    PyFPE_START_PROTECT("is_integer", return NULL)
    o = (floor(x) == x) ? Py_True : Py_False;
    PyFPE_END_PROTECT(x)
    if (errno != 0) {
        PyErr_SetFromErrno(errno == ERANGE ? PyExc_OverflowError :
                             PyExc_ValueError);
        return NULL;
    }
    Py_INCREF(o);
    return o;
}
