_PyDict_Contains(PyObject *op, PyObject *key, long hash)
{
    PyDictObject *mp = (PyDictObject *)op;
    PyDictEntry *ep;

    ep = (mp->ma_lookup)(mp, key, hash);
    return ep == NULL ? -1 : (ep->me_value != NULL);
}
