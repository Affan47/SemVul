PyZlib_flush(compobject *self, PyObject *args)
{
    int err, length = DEFAULTALLOC;
    PyObject *RetVal;
    int flushmode = Z_FINISH;
    unsigned long start_total_out;

    if (!PyArg_ParseTuple(args, "|i:flush", &flushmode))
        return NULL;


    if (flushmode == Z_NO_FLUSH) {
        return PyBytes_FromStringAndSize(NULL, 0);
    }

    if (!(RetVal = PyBytes_FromStringAndSize(NULL, length)))
        return NULL;

    ENTER_ZLIB(self);

    start_total_out = self->zst.total_out;
    self->zst.avail_in = 0;
    self->zst.avail_out = length;
    self->zst.next_out = (unsigned char *)PyBytes_AS_STRING(RetVal);

    Py_BEGIN_ALLOW_THREADS
    err = deflate(&(self->zst), flushmode);
    Py_END_ALLOW_THREADS


    while (err == Z_OK && self->zst.avail_out == 0) {
        if (_PyBytes_Resize(&RetVal, length << 1) < 0) {
            Py_DECREF(RetVal);
            RetVal = NULL;
            goto error;
        }
        self->zst.next_out =
            (unsigned char *)PyBytes_AS_STRING(RetVal) + length;
        self->zst.avail_out = length;
        length = length << 1;

        Py_BEGIN_ALLOW_THREADS
        err = deflate(&(self->zst), flushmode);
        Py_END_ALLOW_THREADS
    }


    if (err == Z_STREAM_END && flushmode == Z_FINISH) {
        err = deflateEnd(&(self->zst));
        if (err != Z_OK) {
            zlib_error(self->zst, err, "while finishing compression");
            Py_DECREF(RetVal);
            RetVal = NULL;
            goto error;
        }
        else
            self->is_initialised = 0;


    } else if (err!=Z_OK && err!=Z_BUF_ERROR) {
        zlib_error(self->zst, err, "while flushing");
        Py_DECREF(RetVal);
        RetVal = NULL;
        goto error;
    }

    if (_PyBytes_Resize(&RetVal, self->zst.total_out - start_total_out) < 0) {
        Py_DECREF(RetVal);
        RetVal = NULL;
    }

 error:
    LEAVE_ZLIB(self);

    return RetVal;
}
