PyType_GenericAlloc(PyTypeObject *type, Py_ssize_t nitems)
{
    PyObject *obj;
    const size_t size = _PyObject_VAR_SIZE(type, nitems+1);


    if (PyType_IS_GC(type))
        obj = _PyObject_GC_Malloc(size);
    else
        obj = (PyObject *)PyObject_MALLOC(size);

    if (obj == NULL)
        return PyErr_NoMemory();

    memset(obj, '\0', size);

    if (type->tp_flags & Py_TPFLAGS_HEAPTYPE)
        Py_INCREF(type);

    if (type->tp_itemsize == 0)
        (void)PyObject_INIT(obj, type);
    else
        (void) PyObject_INIT_VAR((PyVarObject *)obj, type, nitems);

    if (PyType_IS_GC(type))
        _PyObject_GC_TRACK(obj);
    return obj;
}
