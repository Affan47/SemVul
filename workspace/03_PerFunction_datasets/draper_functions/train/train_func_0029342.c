PyDict_Merge(PyObject *a, PyObject *b, int override)
{
    register PyDictObject *mp, *other;
    register Py_ssize_t i, n;
    PyDictKeyEntry *entry;


    if (a == NULL || !PyDict_Check(a) || b == NULL) {
        PyErr_BadInternalCall();
        return -1;
    }
    mp = (PyDictObject*)a;
    if (PyDict_Check(b)) {
        other = (PyDictObject*)b;
        if (other == mp || other->ma_used == 0)

            return 0;
        if (mp->ma_used == 0)


            override = 1;


        if (mp->ma_keys->dk_usable * 3 < other->ma_used * 2)
            if (dictresize(mp, (mp->ma_used + other->ma_used)*2) != 0)
               return -1;
        for (i = 0, n = DK_SIZE(other->ma_keys); i < n; i++) {
            PyObject *value;
            entry = &other->ma_keys->dk_entries[i];
            if (other->ma_values)
                value = other->ma_values[i];
            else
                value = entry->me_value;

            if (value != NULL &&
                (override ||
                 PyDict_GetItem(a, entry->me_key) == NULL)) {
                if (insertdict(mp, entry->me_key,
                               entry->me_hash,
                               value) != 0)
                    return -1;
            }
        }
    }
    else {

        PyObject *keys = PyMapping_Keys(b);
        PyObject *iter;
        PyObject *key, *value;
        int status;

        if (keys == NULL)


            return -1;

        iter = PyObject_GetIter(keys);
        Py_DECREF(keys);
        if (iter == NULL)
            return -1;

        for (key = PyIter_Next(iter); key; key = PyIter_Next(iter)) {
            if (!override && PyDict_GetItem(a, key) != NULL) {
                Py_DECREF(key);
                continue;
            }
            value = PyObject_GetItem(b, key);
            if (value == NULL) {
                Py_DECREF(iter);
                Py_DECREF(key);
                return -1;
            }
            status = PyDict_SetItem(a, key, value);
            Py_DECREF(key);
            Py_DECREF(value);
            if (status < 0) {
                Py_DECREF(iter);
                return -1;
            }
        }
        Py_DECREF(iter);
        if (PyErr_Occurred())

            return -1;
    }
    return 0;
}
