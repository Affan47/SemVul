unpack_from(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *s_object, *fmt, *newargs, *result;
    Py_ssize_t n = PyTuple_GET_SIZE(args);

    if (n == 0) {
        PyErr_SetString(PyExc_TypeError, "missing format argument");
        return NULL;
    }
    fmt = PyTuple_GET_ITEM(args, 0);
    newargs = PyTuple_GetSlice(args, 1, n);
    if (newargs == NULL)
        return NULL;

    s_object = cache_struct(fmt);
    if (s_object == NULL) {
        Py_DECREF(newargs);
        return NULL;
    }
    result = s_unpack_from(s_object, newargs, kwds);
    Py_DECREF(newargs);
    Py_DECREF(s_object);
    return result;
}
