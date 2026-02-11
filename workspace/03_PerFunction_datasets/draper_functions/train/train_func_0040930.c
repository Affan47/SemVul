align_func(PyObject *self, PyObject *obj)
{
    StgDictObject *dict;

    dict = PyType_stgdict(obj);
    if (dict)
        return PyLong_FromSsize_t(dict->align);

    dict = PyObject_stgdict(obj);
    if (dict)
        return PyLong_FromSsize_t(dict->align);

    PyErr_SetString(PyExc_TypeError,
                    "no alignment info");
    return NULL;
}
