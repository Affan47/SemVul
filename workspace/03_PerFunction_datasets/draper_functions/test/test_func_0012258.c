math_modf(PyObject *self, PyObject *arg)
{
    double y, x = PyFloat_AsDouble(arg);
    if (x == -1.0 && PyErr_Occurred())
        return NULL;


    if (!Py_IS_FINITE(x)) {
        if (Py_IS_INFINITY(x))
            return Py_BuildValue("(dd)", copysign(0., x), x);
        else if (Py_IS_NAN(x))
            return Py_BuildValue("(dd)", x, x);
    }

    errno = 0;
    PyFPE_START_PROTECT("in math_modf", return 0);
    x = modf(x, &y);
    PyFPE_END_PROTECT(x);
    return Py_BuildValue("(dd)", x, y);
}
