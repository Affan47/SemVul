unpack_single(char *ptr, const char *fmt, Py_ssize_t itemsize)
{
    PyObject *x, *unpack_from, *mview;

    if (fmt == NULL) {
        fmt = "B";
        itemsize = 1;
    }

    unpack_from = PyObject_GetAttrString(structmodule, "unpack_from");
    if (unpack_from == NULL)
        return NULL;

    mview = PyMemoryView_FromMemory(ptr, itemsize, PyBUF_READ);
    if (mview == NULL) {
        Py_DECREF(unpack_from);
        return NULL;
    }

    x = PyObject_CallFunction(unpack_from, "sO", fmt, mview);
    Py_DECREF(unpack_from);
    Py_DECREF(mview);
    if (x == NULL)
        return NULL;

    if (PyTuple_GET_SIZE(x) == 1) {
        PyObject *tmp = PyTuple_GET_ITEM(x, 0);
        Py_INCREF(tmp);
        Py_DECREF(x);
        return tmp;
    }

    return x;
}
