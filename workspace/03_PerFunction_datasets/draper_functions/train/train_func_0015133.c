textiowrapper_truncate(textio *self, PyObject *args)
{
    PyObject *pos = Py_None;
    PyObject *res;

    CHECK_INITIALIZED(self)
    if (!PyArg_ParseTuple(args, "|O:truncate", &pos)) {
        return NULL;
    }

    res = PyObject_CallMethodObjArgs((PyObject *) self, _PyIO_str_flush, NULL);
    if (res == NULL)
        return NULL;
    Py_DECREF(res);

    return PyObject_CallMethodObjArgs(self->buffer, _PyIO_str_truncate, pos, NULL);
}
