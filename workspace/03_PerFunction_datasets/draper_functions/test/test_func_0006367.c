PyZlib_decompressobj(PyObject *selfptr, PyObject *args)
{
    int wbits=DEF_WBITS, err;
    compobject *self;
    if (!PyArg_ParseTuple(args, "|i:decompressobj", &wbits))
        return NULL;

    self = newcompobject(&Decomptype);
    if (self == NULL)
        return(NULL);
    self->zst.zalloc = (alloc_func)NULL;
    self->zst.zfree = (free_func)Z_NULL;
    self->zst.next_in = NULL;
    self->zst.avail_in = 0;
    err = inflateInit2(&self->zst, wbits);
    switch(err) {
    case (Z_OK):
        self->is_initialised = 1;
        return (PyObject*)self;
    case(Z_STREAM_ERROR):
        Py_DECREF(self);
        PyErr_SetString(PyExc_ValueError, "Invalid initialization option");
        return NULL;
    case (Z_MEM_ERROR):
        Py_DECREF(self);
        PyErr_SetString(PyExc_MemoryError,
                        "Can't allocate memory for decompression object");
        return NULL;
    default:
        zlib_error(self->zst, err, "while creating decompression object");
        Py_DECREF(self);
        return NULL;
    }
}
