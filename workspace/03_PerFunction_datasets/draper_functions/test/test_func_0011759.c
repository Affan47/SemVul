_PyType_Lookup(PyTypeObject *type, PyObject *name)
{
    Py_ssize_t i, n;
    PyObject *mro, *res, *base, *dict;
    unsigned int h;

    if (MCACHE_CACHEABLE_NAME(name) &&
        PyType_HasFeature(type, Py_TPFLAGS_VALID_VERSION_TAG)) {

        h = MCACHE_HASH_METHOD(type, name);
        if (method_cache[h].version == type->tp_version_tag &&
            method_cache[h].name == name)
            return method_cache[h].value;
    }


    mro = type->tp_mro;


    if (mro == NULL)
        return NULL;

    res = NULL;


    Py_INCREF(mro);
    assert(PyTuple_Check(mro));
    n = PyTuple_GET_SIZE(mro);
    for (i = 0; i < n; i++) {
        base = PyTuple_GET_ITEM(mro, i);
        assert(PyType_Check(base));
        dict = ((PyTypeObject *)base)->tp_dict;
        assert(dict && PyDict_Check(dict));
        res = PyDict_GetItem(dict, name);
        if (res != NULL)
            break;
    }
    Py_DECREF(mro);

    if (MCACHE_CACHEABLE_NAME(name) && assign_version_tag(type)) {
        h = MCACHE_HASH_METHOD(type, name);
        method_cache[h].version = type->tp_version_tag;
        method_cache[h].value = res;
        Py_INCREF(name);
        Py_DECREF(method_cache[h].name);
        method_cache[h].name = name;
    }
    return res;
}
