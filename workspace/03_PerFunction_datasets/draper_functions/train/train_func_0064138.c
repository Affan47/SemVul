PyDict_GetItem(PyObject *op, PyObject *key)
{
    long hash;
    PyDictObject *mp = (PyDictObject *)op;
    PyDictEntry *ep;
    PyThreadState *tstate;
    if (!PyDict_Check(op))
        return NULL;
    if (!PyString_CheckExact(key) ||
        (hash = ((PyStringObject *) key)->ob_shash) == -1)
    {
        hash = PyObject_Hash(key);
        if (hash == -1) {
            PyErr_Clear();
            return NULL;
        }
    }


    tstate = _PyThreadState_Current;
    if (tstate != NULL && tstate->curexc_type != NULL) {

        PyObject *err_type, *err_value, *err_tb;
        PyErr_Fetch(&err_type, &err_value, &err_tb);
        ep = (mp->ma_lookup)(mp, key, hash);

        PyErr_Restore(err_type, err_value, err_tb);
        if (ep == NULL)
            return NULL;
    }
    else {
        ep = (mp->ma_lookup)(mp, key, hash);
        if (ep == NULL) {
            PyErr_Clear();
            return NULL;
        }
    }
    return ep->me_value;
}
