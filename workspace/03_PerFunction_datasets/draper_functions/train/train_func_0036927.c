BZ2Decompressor_init(BZ2Decompressor *self, PyObject *args, PyObject *kwargs)
{
    int bzerror;

    if (!PyArg_ParseTuple(args, ":BZ2Decompressor"))
        return -1;

#ifdef WITH_THREAD
    self->lock = PyThread_allocate_lock();
    if (self->lock == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allocate lock");
        return -1;
    }
#endif

    self->unused_data = PyBytes_FromStringAndSize("", 0);
    if (self->unused_data == NULL)
        goto error;

    bzerror = BZ2_bzDecompressInit(&self->bzs, 0, 0);
    if (catch_bz2_error(bzerror))
        goto error;

    return 0;

error:
    Py_CLEAR(self->unused_data);
#ifdef WITH_THREAD
    PyThread_free_lock(self->lock);
    self->lock = NULL;
#endif
    return -1;
}
