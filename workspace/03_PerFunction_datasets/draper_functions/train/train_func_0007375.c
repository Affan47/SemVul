buffered_close(buffered *self, PyObject *args)
{
    PyObject *res = NULL, *exc = NULL, *val, *tb;
    int r;

    CHECK_INITIALIZED(self)
    if (!ENTER_BUFFERED(self))
        return NULL;

    r = buffered_closed(self);
    if (r < 0)
        goto end;
    if (r > 0) {
        res = Py_None;
        Py_INCREF(res);
        goto end;
    }

    LEAVE_BUFFERED(self)
    res = PyObject_CallMethodObjArgs((PyObject *)self, _PyIO_str_flush, NULL);
    if (!ENTER_BUFFERED(self))
        return NULL;
    if (res == NULL)
        PyErr_Fetch(&exc, &val, &tb);
    else
        Py_DECREF(res);

    res = PyObject_CallMethodObjArgs(self->raw, _PyIO_str_close, NULL);

    if (exc != NULL) {
        if (res != NULL) {
            Py_CLEAR(res);
            PyErr_Restore(exc, val, tb);
        }
        else {
            Py_DECREF(exc);
            Py_XDECREF(val);
            Py_XDECREF(tb);
        }
    }

end:
    LEAVE_BUFFERED(self)
    return res;
}
