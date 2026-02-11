PyZlib_uncopy(compobject *self)
{
    compobject *retval = NULL;
    int err;

    retval = newcompobject(&Decomptype);
    if (!retval) return NULL;


    ENTER_ZLIB(self);
    err = inflateCopy(&retval->zst, &self->zst);
    switch(err) {
    case(Z_OK):
        break;
    case(Z_STREAM_ERROR):
        PyErr_SetString(PyExc_ValueError, "Inconsistent stream state");
        goto error;
    case(Z_MEM_ERROR):
        PyErr_SetString(PyExc_MemoryError,
                        "Can't allocate memory for decompression object");
        goto error;
    default:
        zlib_error(self->zst, err, "while copying decompression object");
        goto error;
    }

    Py_INCREF(self->unused_data);
    Py_INCREF(self->unconsumed_tail);
    Py_XDECREF(retval->unused_data);
    Py_XDECREF(retval->unconsumed_tail);
    retval->unused_data = self->unused_data;
    retval->unconsumed_tail = self->unconsumed_tail;
    retval->eof = self->eof;


    retval->is_initialised = 1;

    LEAVE_ZLIB(self);
    return (PyObject *)retval;

error:
    LEAVE_ZLIB(self);
    Py_XDECREF(retval);
    return NULL;
}
