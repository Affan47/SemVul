bytearray_insert(PyByteArrayObject *self, PyObject *args)
{
    PyObject *value;
    int ival;
    Py_ssize_t where, n = Py_SIZE(self);
    char *buf;

    if (!PyArg_ParseTuple(args, "nO:insert", &where, &value))
        return NULL;

    if (n == PY_SSIZE_T_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "cannot add more objects to bytearray");
        return NULL;
    }
    if (!_getbytevalue(value, &ival))
        return NULL;
    if (PyByteArray_Resize((PyObject *)self, n + 1) < 0)
        return NULL;
    buf = PyByteArray_AS_STRING(self);

    if (where < 0) {
        where += n;
        if (where < 0)
            where = 0;
    }
    if (where > n)
        where = n;
    memmove(buf + where + 1, buf + where, n - where);
    buf[where] = ival;

    Py_RETURN_NONE;
}
