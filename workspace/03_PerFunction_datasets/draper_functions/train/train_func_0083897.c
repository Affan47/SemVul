get_longlong(PyObject *v, PY_LONG_LONG *p)
{
    PY_LONG_LONG x;

    v = get_pylong(v);
    if (v == NULL)
        return -1;
    assert(PyLong_Check(v));
    x = PyLong_AsLongLong(v);
    Py_DECREF(v);
    if (x == (PY_LONG_LONG)-1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            PyErr_SetString(StructError,
                            "argument out of range");
        return -1;
    }
    *p = x;
    return 0;
}
