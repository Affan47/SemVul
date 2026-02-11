set_merge(PySetObject *so, PyObject *otherset)
{
    PySetObject *other;
    PyObject *key;
    Py_hash_t hash;
    Py_ssize_t i;
    setentry *entry;

    assert (PyAnySet_Check(so));
    assert (PyAnySet_Check(otherset));

    other = (PySetObject*)otherset;
    if (other == so || other->used == 0)

        return 0;


    if ((so->fill + other->used)*3 >= (so->mask+1)*2) {
       if (set_table_resize(so, (so->used + other->used)*2) != 0)
           return -1;
    }
    for (i = 0; i <= other->mask; i++) {
        entry = &other->table[i];
        key = entry->key;
        hash = entry->hash;
        if (key != NULL &&
            key != dummy) {
            Py_INCREF(key);
            if (set_insert_key(so, key, hash) == -1) {
                Py_DECREF(key);
                return -1;
            }
        }
    }
    return 0;
}
