Writer_dealloc(WriterObj *self)
{
    PyObject_GC_UnTrack(self);
    Py_XDECREF(self->dialect);
    Py_XDECREF(self->writeline);
    if (self->rec != NULL)
        PyMem_Free(self->rec);
    PyObject_GC_Del(self);
}
