partial_dealloc(partialobject *pto)
{
    PyObject_GC_UnTrack(pto);
    if (pto->weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *) pto);
    Py_XDECREF(pto->fn);
    Py_XDECREF(pto->args);
    Py_XDECREF(pto->kw);
    Py_XDECREF(pto->dict);
    Py_TYPE(pto)->tp_free(pto);
}
