BaseException_dealloc(PyBaseExceptionObject *self)
{
    _PyObject_GC_UNTRACK(self);
    BaseException_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
}
