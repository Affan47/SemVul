PyCData_clear(CDataObject *self)
{
    StgDictObject *dict = PyObject_stgdict((PyObject *)self);
    assert(dict);
    Py_CLEAR(self->b_objects);
    if ((self->b_needsfree)
        && ((size_t)dict->size > sizeof(self->b_value)))
        PyMem_Free(self->b_ptr);
    self->b_ptr = NULL;
    Py_CLEAR(self->b_base);
    return 0;
}
