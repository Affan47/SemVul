PyDict_DelItem(PyObject *op, PyObject *key)
{
    PyDictObject *mp;
    Py_hash_t hash;
    PyDictKeyEntry *ep;
    PyObject *old_key, *old_value;
    PyObject **value_addr;

    if (!PyDict_Check(op)) {
        PyErr_BadInternalCall();
        return -1;
    }
    assert(key);
    if (!PyUnicode_CheckExact(key) ||
        (hash = ((PyASCIIObject *) key)->hash) == -1) {
        hash = PyObject_Hash(key);
        if (hash == -1)
            return -1;
    }
    mp = (PyDictObject *)op;
    ep = (mp->ma_keys->dk_lookup)(mp, key, hash, &value_addr);
    if (ep == NULL)
        return -1;
    if (*value_addr == NULL) {
        _PyErr_SetKeyError(key);
        return -1;
    }
    old_value = *value_addr;
    *value_addr = NULL;
    mp->ma_used--;
    if (!_PyDict_HasSplitTable(mp)) {
        ENSURE_ALLOWS_DELETIONS(mp);
        old_key = ep->me_key;
        Py_INCREF(dummy);
        ep->me_key = dummy;
        Py_DECREF(old_key);
    }
    Py_DECREF(old_value);
    return 0;
}
