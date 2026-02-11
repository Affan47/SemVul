set_update_internal(PySetObject *so, PyObject *other)
{
    PyObject *key, *it;

    if (PyAnySet_Check(other))
        return set_merge(so, other);

    if (PyDict_CheckExact(other)) {
        PyObject *value;
        Py_ssize_t pos = 0;
        Py_hash_t hash;
        Py_ssize_t dictsize = PyDict_Size(other);


        if (dictsize == -1)
            return -1;
        if ((so->fill + dictsize)*3 >= (so->mask+1)*2) {
            if (set_table_resize(so, (so->used + dictsize)*2) != 0)
                return -1;
        }
        while (_PyDict_Next(other, &pos, &key, &value, &hash)) {
            setentry an_entry;

            an_entry.hash = hash;
            an_entry.key = key;
            if (set_add_entry(so, &an_entry) == -1)
                return -1;
        }
        return 0;
    }

    it = PyObject_GetIter(other);
    if (it == NULL)
        return -1;

    while ((key = PyIter_Next(it)) != NULL) {
        if (set_add_key(so, key) == -1) {
            Py_DECREF(it);
            Py_DECREF(key);
            return -1;
        }
        Py_DECREF(key);
    }
    Py_DECREF(it);
    if (PyErr_Occurred())
        return -1;
    return 0;
}
