zip_longest_dealloc(ziplongestobject *lz)
{
    PyObject_GC_UnTrack(lz);
    Py_XDECREF(lz->ittuple);
    Py_XDECREF(lz->result);
    Py_XDECREF(lz->fillvalue);
    Py_TYPE(lz)->tp_free(lz);
}
