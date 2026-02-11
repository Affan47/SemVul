CreateSwappedType(PyTypeObject *type, PyObject *args, PyObject *kwds,
                                   PyObject *proto, struct fielddesc *fmt)
{
    PyTypeObject *result;
    StgDictObject *stgdict;
    PyObject *name = PyTuple_GET_ITEM(args, 0);
    PyObject *newname;
    PyObject *swapped_args;
    static PyObject *suffix;
    Py_ssize_t i;

    swapped_args = PyTuple_New(PyTuple_GET_SIZE(args));
    if (!swapped_args)
        return NULL;

    if (suffix == NULL)
#ifdef WORDS_BIGENDIAN
        suffix = PyUnicode_InternFromString("_le");
#else
        suffix = PyUnicode_InternFromString("_be");
#endif

    newname = PyUnicode_Concat(name, suffix);
    if (newname == NULL) {
        return NULL;
    }

    PyTuple_SET_ITEM(swapped_args, 0, newname);
    for (i=1; i<PyTuple_GET_SIZE(args); ++i) {
        PyObject *v = PyTuple_GET_ITEM(args, i);
        Py_INCREF(v);
        PyTuple_SET_ITEM(swapped_args, i, v);
    }


    result = (PyTypeObject *)PyType_Type.tp_new(type, swapped_args, kwds);
    Py_DECREF(swapped_args);
    if (result == NULL)
        return NULL;

    stgdict = (StgDictObject *)PyObject_CallObject(
        (PyObject *)&PyCStgDict_Type, NULL);
    if (!stgdict)
        return NULL;

    stgdict->ffi_type_pointer = *fmt->pffi_type;
    stgdict->align = fmt->pffi_type->alignment;
    stgdict->length = 0;
    stgdict->size = fmt->pffi_type->size;
    stgdict->setfunc = fmt->setfunc_swapped;
    stgdict->getfunc = fmt->getfunc_swapped;

    Py_INCREF(proto);
    stgdict->proto = proto;


    if (-1 == PyDict_Update((PyObject *)stgdict, result->tp_dict)) {
        Py_DECREF(result);
        Py_DECREF((PyObject *)stgdict);
        return NULL;
    }
    Py_DECREF(result->tp_dict);
    result->tp_dict = (PyObject *)stgdict;

    return (PyObject *)result;
}
