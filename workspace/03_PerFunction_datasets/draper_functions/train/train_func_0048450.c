buffered_truncate(buffered *self, PyObject *args)
{
    PyObject *pos = Py_None;
    PyObject *res = NULL;

    CHECK_INITIALIZED(self)
    if (!PyArg_ParseTuple(args, "|O:truncate", &pos)) {
        return NULL;
    }

    if (!ENTER_BUFFERED(self))
        return NULL;

    if (self->writable) {
        res = buffered_flush_and_rewind_unlocked(self);
        if (res == NULL)
            goto end;
        Py_CLEAR(res);
    }
    res = PyObject_CallMethodObjArgs(self->raw, _PyIO_str_truncate, pos, NULL);
    if (res == NULL)
        goto end;

    if (_buffered_raw_tell(self) == -1)
        PyErr_Clear();

end:
    LEAVE_BUFFERED(self)
    return res;
}
