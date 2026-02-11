PyCData_get(PyObject *type, GETFUNC getfunc, PyObject *src,
          Py_ssize_t index, Py_ssize_t size, char *adr)
{
    StgDictObject *dict;
    if (getfunc)
        return getfunc(adr, size);
    assert(type);
    dict = PyType_stgdict(type);
    if (dict && dict->getfunc && !_ctypes_simple_instance(type))
        return dict->getfunc(adr, size);
    return PyCData_FromBaseObj(type, src, index, adr);
}
