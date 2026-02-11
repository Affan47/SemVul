zlib_Compress_copy_impl(compobject *self)

{
    compobject *retval = NULL;
    int err;

    retval = newcompobject(&Comptype);
    if (!retval) return NULL;


    ENTER_ZLIB(self);
    err = deflateCopy(&retval->zst, &self->zst);
    switch(err) {
    case(Z_OK):
        break;
    case(Z_STREAM_ERROR):
        PyErr_SetString(PyExc_ValueError, "Inconsistent stream state");
        goto error;
    case(Z_MEM_ERROR):
        PyErr_SetString(PyExc_MemoryError,
                        "Can't allocate memory for compression object");
        goto error;
    default:
        zlib_error(self->zst, err, "while copying compression object");
        goto error;
    }
    Py_INCREF(self->unused_data);
    Py_INCREF(self->unconsumed_tail);
    Py_XINCREF(self->zdict);
    Py_XDECREF(retval->unused_data);
    Py_XDECREF(retval->unconsumed_tail);
    Py_XDECREF(retval->zdict);
    retval->unused_data = self->unused_data;
    retval->unconsumed_tail = self->unconsumed_tail;
    retval->zdict = self->zdict;
    retval->eof = self->eof;


    retval->is_initialised = 1;

    LEAVE_ZLIB(self);
    return (PyObject *)retval;

error:
    LEAVE_ZLIB(self);
    Py_XDECREF(retval);
    return NULL;
}
