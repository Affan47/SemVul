PyCFuncPtrType_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyTypeObject *result;
    StgDictObject *stgdict;

    stgdict = (StgDictObject *)PyObject_CallObject(
        (PyObject *)&PyCStgDict_Type, NULL);
    if (!stgdict)
        return NULL;

    stgdict->paramfunc = PyCFuncPtrType_paramfunc;


    stgdict->format = _ctypes_alloc_format_string(NULL, "X{}");
    stgdict->flags |= TYPEFLAG_ISPOINTER;


    result = (PyTypeObject *)PyType_Type.tp_new(type, args, kwds);
    if (result == NULL) {
        Py_DECREF((PyObject *)stgdict);
        return NULL;
    }


    if (-1 == PyDict_Update((PyObject *)stgdict, result->tp_dict)) {
        Py_DECREF(result);
        Py_DECREF((PyObject *)stgdict);
        return NULL;
    }
    Py_DECREF(result->tp_dict);
    result->tp_dict = (PyObject *)stgdict;

    if (-1 == make_funcptrtype_dict(stgdict)) {
        Py_DECREF(result);
        return NULL;
    }

    return (PyObject *)result;
}
