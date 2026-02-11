buffered_dealloc(buffered *self)
{
    if (self->ok && _PyIOBase_finalize((PyObject *) self) < 0)
        return;
    _PyObject_GC_UNTRACK(self);
    self->ok = 0;
    if (self->weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *)self);
    Py_CLEAR(self->raw);
    if (self->buffer) {
        PyMem_Free(self->buffer);
        self->buffer = NULL;
    }
#ifdef WITH_THREAD
    if (self->lock) {
        PyThread_free_lock(self->lock);
        self->lock = NULL;
    }
#endif
    Py_CLEAR(self->dict);
    Py_TYPE(self)->tp_free((PyObject *)self);
}
