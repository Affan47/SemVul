BaseException_getitem(PyBaseExceptionObject *self, Py_ssize_t index)
{
    if (PyErr_WarnPy3k("__getitem__ not supported for exception "
                       "classes in 3.x; use args attribute", 1) < 0)
        return NULL;
    return PySequence_GetItem(self->args, index);
}
