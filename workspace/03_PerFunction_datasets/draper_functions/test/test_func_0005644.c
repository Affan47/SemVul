PyCPointerType_SetProto(StgDictObject *stgdict, PyObject *proto)
{
    if (!proto || !PyType_Check(proto)) {
        PyErr_SetString(PyExc_TypeError,
                        "_type_ must be a type");
        return -1;
    }
    if (!PyType_stgdict(proto)) {
        PyErr_SetString(PyExc_TypeError,
                        "_type_ must have storage info");
        return -1;
    }
    Py_INCREF(proto);
    Py_XDECREF(stgdict->proto);
    stgdict->proto = proto;
    return 0;
}
