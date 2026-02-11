PyFloat_ClearFreeList(void)
{
    PyFloatObject *f = free_list, *next;
    int i = numfree;
    while (f) {
        next = (PyFloatObject*) Py_TYPE(f);
        PyObject_FREE(f);
        f = next;
    }
    free_list = NULL;
    numfree = 0;
    return i;
}
