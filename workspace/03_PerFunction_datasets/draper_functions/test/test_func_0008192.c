dictiter_iternextkey(dictiterobject *di)
{
    PyObject *key;
    register Py_ssize_t i, mask, offset;
    register PyDictKeysObject *k;
    PyDictObject *d = di->di_dict;
    PyObject **value_ptr;

    if (d == NULL)
        return NULL;
    assert (PyDict_Check(d));

    if (di->di_used != d->ma_used) {
        PyErr_SetString(PyExc_RuntimeError,
                        "dictionary changed size during iteration");
        di->di_used = -1;
        return NULL;
    }

    i = di->di_pos;
    if (i < 0)
        goto fail;
    k = d->ma_keys;
    if (d->ma_values) {
        value_ptr = &d->ma_values[i];
        offset = sizeof(PyObject *);
    }
    else {
        value_ptr = &k->dk_entries[i].me_value;
        offset = sizeof(PyDictKeyEntry);
    }
    mask = DK_SIZE(k)-1;
    while (i <= mask && *value_ptr == NULL) {
        value_ptr = (PyObject **)(((char *)value_ptr) + offset);
        i++;
    }
    di->di_pos = i+1;
    if (i > mask)
        goto fail;
    di->len--;
    key = k->dk_entries[i].me_key;
    Py_INCREF(key);
    return key;

fail:
    Py_DECREF(d);
    di->di_dict = NULL;
    return NULL;
}
