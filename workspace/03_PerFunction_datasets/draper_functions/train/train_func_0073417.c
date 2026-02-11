dict_setdefault(register PyDictObject *mp, PyObject *args)
{
    PyObject *key;
    PyObject *failobj = Py_None;
    PyObject *val = NULL;
    Py_hash_t hash;
    PyDictKeyEntry *ep;
    PyObject **value_addr;

    if (!PyArg_UnpackTuple(args, "setdefault", 1, 2, &key, &failobj))
        return NULL;

    if (!PyUnicode_CheckExact(key) ||
        (hash = ((PyASCIIObject *) key)->hash) == -1) {
        hash = PyObject_Hash(key);
        if (hash == -1)
            return NULL;
    }
    ep = (mp->ma_keys->dk_lookup)(mp, key, hash, &value_addr);
    if (ep == NULL)
        return NULL;
    val = *value_addr;
    if (val == NULL) {
        Py_INCREF(failobj);
        Py_INCREF(key);
        if (mp->ma_keys->dk_usable <= 0) {

            if (insertion_resize(mp) < 0)
                return NULL;
            ep = find_empty_slot(mp, key, hash, &value_addr);
        }
        MAINTAIN_TRACKING(mp, key, failobj);
        ep->me_key = key;
        ep->me_hash = hash;
        *value_addr = failobj;
        val = failobj;
        mp->ma_keys->dk_usable--;
        mp->ma_used++;
    }
    Py_INCREF(val);
    return val;
}
