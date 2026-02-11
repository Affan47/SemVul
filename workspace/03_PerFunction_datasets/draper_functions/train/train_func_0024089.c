cmath_polar(PyObject *self, PyObject *args)
{
    Py_complex z;
    double r, phi;
    if (!PyArg_ParseTuple(args, "D:polar", &z))
        return NULL;
    PyFPE_START_PROTECT("polar function", return 0)
    phi = c_atan2(z);
    r = c_abs(z);
    PyFPE_END_PROTECT(r)
    if (errno != 0)
        return math_error();
    else
        return Py_BuildValue("dd", r, phi);
}
