long_and(PyObject *a, PyObject *b)
{
    PyObject *c;
    CHECK_BINOP(a, b);
    c = long_bitwise((PyLongObject*)a, '&', (PyLongObject*)b);
    return c;
}
