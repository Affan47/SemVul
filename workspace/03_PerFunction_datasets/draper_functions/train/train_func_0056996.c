PyList_ClearFreeList(void)
{
    PyListObject *op;
    int ret = numfree;
    while (numfree) {
        op = free_list[--numfree];
        assert(PyList_CheckExact(op));
        PyObject_GC_Del(op);
    }
    return ret;
}
