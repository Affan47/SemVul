bufferedwriter_init(buffered *self, PyObject *args, PyObject *kwds)
{
    char *kwlist[] = {"raw", "buffer_size", NULL};
    Py_ssize_t buffer_size = DEFAULT_BUFFER_SIZE;
    PyObject *raw;

    self->ok = 0;
    self->detached = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|n:BufferedWriter", kwlist,
                                     &raw, &buffer_size)) {
        return -1;
    }

    if (_PyIOBase_check_writable(raw, Py_True) == NULL)
        return -1;

    Py_CLEAR(self->raw);
    Py_INCREF(raw);
    self->raw = raw;
    self->readable = 0;
    self->writable = 1;

    self->buffer_size = buffer_size;
    if (_buffered_init(self) < 0)
        return -1;
    _bufferedwriter_reset_buf(self);
    self->pos = 0;

    self->fast_closed_checks = (Py_TYPE(self) == &PyBufferedWriter_Type &&
                                Py_TYPE(raw) == &PyFileIO_Type);

    self->ok = 1;
    return 0;
}
