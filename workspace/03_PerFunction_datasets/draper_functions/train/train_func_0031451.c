dictresize(PyDictObject *mp, Py_ssize_t minused)
{
    Py_ssize_t newsize;
    PyDictKeysObject *oldkeys;
    PyObject **oldvalues;
    Py_ssize_t i, oldsize;


    for (newsize = PyDict_MINSIZE_COMBINED;
         newsize <= minused && newsize > 0;
         newsize <<= 1)
        ;
    if (newsize <= 0) {
        PyErr_NoMemory();
        return -1;
    }
    oldkeys = mp->ma_keys;
    oldvalues = mp->ma_values;

    mp->ma_keys = new_keys_object(newsize);
    if (mp->ma_keys == NULL) {
        mp->ma_keys = oldkeys;
        return -1;
    }
    if (oldkeys->dk_lookup == lookdict)
        mp->ma_keys->dk_lookup = lookdict;
    oldsize = DK_SIZE(oldkeys);
    mp->ma_values = NULL;

    if (oldsize == 1) {
        assert(oldkeys == Py_EMPTY_KEYS);
        DK_DECREF(oldkeys);
        return 0;
    }


    if (oldvalues != NULL) {
        for (i = 0; i < oldsize; i++) {
            if (oldvalues[i] != NULL) {
                Py_INCREF(oldkeys->dk_entries[i].me_key);
                oldkeys->dk_entries[i].me_value = oldvalues[i];
            }
        }
    }

    for (i = 0; i < oldsize; i++) {
        PyDictKeyEntry *ep = &oldkeys->dk_entries[i];
        if (ep->me_value != NULL) {
            assert(ep->me_key != dummy);
            insertdict_clean(mp, ep->me_key, ep->me_hash, ep->me_value);
        }
    }
    mp->ma_keys->dk_usable -= mp->ma_used;
    if (oldvalues != NULL) {

        for (i = 0; i < oldsize; i++)
            oldkeys->dk_entries[i].me_value = NULL;
        assert(oldvalues != empty_values);
        free_values(oldvalues);
        DK_DECREF(oldkeys);
    }
    else {
        assert(oldkeys->dk_lookup != lookdict_split);
        if (oldkeys->dk_lookup != lookdict_unicode_nodummy) {
            PyDictKeyEntry *ep0 = &oldkeys->dk_entries[0];
            for (i = 0; i < oldsize; i++) {
                if (ep0[i].me_key == dummy)
                    Py_DECREF(dummy);
            }
        }
        assert(oldkeys->dk_refcnt == 1);
        PyMem_FREE(oldkeys);
    }
    return 0;
}
