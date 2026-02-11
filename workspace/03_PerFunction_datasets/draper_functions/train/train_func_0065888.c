_PyLong_AsUnsignedLongLongMask(PyObject *vv)
{
    PyLongObject *v;
    unsigned PY_LONG_LONG x;
    Py_ssize_t i;
    int sign;

    if (vv == NULL || !PyLong_Check(vv)) {
        PyErr_BadInternalCall();
        return (unsigned long) -1;
    }
    v = (PyLongObject *)vv;
    switch(Py_SIZE(v)) {
    case 0: return 0;
    case 1: return v->ob_digit[0];
    }
    i = Py_SIZE(v);
    sign = 1;
    x = 0;
    if (i < 0) {
        sign = -1;
        i = -i;
    }
    while (--i >= 0) {
        x = (x << PyLong_SHIFT) | v->ob_digit[i];
    }
    return x * sign;
}
