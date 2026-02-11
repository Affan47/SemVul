type_set_abstractmethods(PyTypeObject *type, PyObject *value, void *context)
{


    int abstract, res;
    if (value != NULL) {
        abstract = PyObject_IsTrue(value);
        if (abstract < 0)
            return -1;
        res = _PyDict_SetItemId(type->tp_dict, &PyId___abstractmethods__, value);
    }
    else {
        abstract = 0;
        res = _PyDict_DelItemId(type->tp_dict, &PyId___abstractmethods__);
        if (res && PyErr_ExceptionMatches(PyExc_KeyError)) {
            PyObject *message = _PyUnicode_FromId(&PyId___abstractmethods__);
            if (message)
                PyErr_SetObject(PyExc_AttributeError, message);
            return -1;
        }
    }
    if (res == 0) {
        PyType_Modified(type);
        if (abstract)
            type->tp_flags |= Py_TPFLAGS_IS_ABSTRACT;
        else
            type->tp_flags &= ~Py_TPFLAGS_IS_ABSTRACT;
    }
    return res;
}
