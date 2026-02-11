dict_fromkeys(PyObject *cls, PyObject *args)
{
    PyObject *seq;
    PyObject *value = Py_None;
    PyObject *it;
    PyObject *key;
    PyObject *d;
    int status;

    if (!PyArg_UnpackTuple(args, "fromkeys", 1, 2, &seq, &value))
        return NULL;

    d = PyObject_CallObject(cls, NULL);
    if (d == NULL)
        return NULL;

    if (PyDict_CheckExact(d) && ((PyDictObject *)d)->ma_used == 0) {
        if (PyDict_CheckExact(seq)) {
            PyDictObject *mp = (PyDictObject *)d;
            PyObject *oldvalue;
            Py_ssize_t pos = 0;
            PyObject *key;
            long hash;

            if (dictresize(mp, Py_SIZE(seq))) {
                Py_DECREF(d);
                return NULL;
            }

            while (_PyDict_Next(seq, &pos, &key, &oldvalue, &hash)) {
                Py_INCREF(key);
                Py_INCREF(value);
                if (insertdict(mp, key, hash, value)) {
                    Py_DECREF(d);
                    return NULL;
                }
            }
            return d;
        }
        if (PyAnySet_CheckExact(seq)) {
            PyDictObject *mp = (PyDictObject *)d;
            Py_ssize_t pos = 0;
            PyObject *key;
            long hash;

            if (dictresize(mp, PySet_GET_SIZE(seq))) {
                Py_DECREF(d);
                return NULL;
            }

            while (_PySet_NextEntry(seq, &pos, &key, &hash)) {
                Py_INCREF(key);
                Py_INCREF(value);
                if (insertdict(mp, key, hash, value)) {
                    Py_DECREF(d);
                    return NULL;
                }
            }
            return d;
        }
    }

    it = PyObject_GetIter(seq);
    if (it == NULL){
        Py_DECREF(d);
        return NULL;
    }

    if (PyDict_CheckExact(d)) {
        while ((key = PyIter_Next(it)) != NULL) {
            status = PyDict_SetItem(d, key, value);
            Py_DECREF(key);
            if (status < 0)
                goto Fail;
        }
    } else {
        while ((key = PyIter_Next(it)) != NULL) {
            status = PyObject_SetItem(d, key, value);
            Py_DECREF(key);
            if (status < 0)
                goto Fail;
        }
    }

    if (PyErr_Occurred())
        goto Fail;
    Py_DECREF(it);
    return d;

Fail:
    Py_DECREF(it);
    Py_DECREF(d);
    return NULL;
}
