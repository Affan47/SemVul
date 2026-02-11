memory_release(PyMemoryViewObject *self)
{
    if (_memory_release(self) < 0)
        return NULL;
    Py_RETURN_NONE;
}
