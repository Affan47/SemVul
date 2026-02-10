complex_classic_div(PyObject *v, PyObject *w)
{
    Py_complex quot;
    Py_complex a, b;
    TO_COMPLEX(v, a);
    TO_COMPLEX(w, b);
    if (Py_DivisionWarningFlag >= 2 &&
        PyErr_Warn(PyExc_DeprecationWarning,
                   "classic complex division") < 0)
        return NULL;

    PyFPE_START_PROTECT("complex_classic_div", return 0)
    errno = 0;
    quot = c_quot(a, b);
    PyFPE_END_PROTECT(quot)
    if (errno == EDOM) {
        PyErr_SetString(PyExc_ZeroDivisionError, "complex division by zero");
        return NULL;
    }
    return PyComplex_FromCComplex(quot);
}
