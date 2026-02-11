Compressor_flush(Compressor *self, PyObject *noargs)
{
    PyObject *result = NULL;

    ACQUIRE_LOCK(self);
    if (self->flushed) {
        PyErr_SetString(PyExc_ValueError, "Repeated call to flush()");
    } else {
        self->flushed = 1;
        result = compress(self, NULL, 0, LZMA_FINISH);
    }
    RELEASE_LOCK(self);
    return result;
}
