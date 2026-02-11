PyDict_Copy(PyObject *o)
{
    PyObject *copy;
    PyDictObject *mp;
    Py_ssize_t i, n;

    if (o == NULL || !PyDict_Check(o)) {
        PyErr_BadInternalCall();
        return NULL;
    }
    mp = (PyDictObject *)o;
    if (_PyDict_HasSplitTable(mp)) {
        PyDictObject *split_copy;
        PyObject **newvalues = new_values(DK_SIZE(mp->ma_keys));
        if (newvalues == NULL)
            return PyErr_NoMemory();
        split_copy = PyObject_GC_New(PyDictObject, &PyDict_Type);
        if (split_copy == NULL) {
            free_values(newvalues);
            return NULL;
        }
        split_copy->ma_values = newvalues;
        split_copy->ma_keys = mp->ma_keys;
        split_copy->ma_used = mp->ma_used;
        DK_INCREF(mp->ma_keys);
        for (i = 0, n = DK_SIZE(mp->ma_keys); i < n; i++) {
            PyObject *value = mp->ma_values[i];
            Py_XINCREF(value);
            split_copy->ma_values[i] = value;
        }
        if (_PyObject_GC_IS_TRACKED(mp))
            _PyObject_GC_TRACK(split_copy);
        return (PyObject *)split_copy;
    }
    copy = PyDict_New();
    if (copy == NULL)
        return NULL;
    if (PyDict_Merge(copy, o, 1) == 0)
        return copy;
    Py_DECREF(copy);
    return NULL;
}
