new_dict_with_shared_keys(PyDictKeysObject *keys)
{
    PyObject **values;
    Py_ssize_t i, size;

    size = DK_SIZE(keys);
    values = new_values(size);
    if (values == NULL) {
        DK_DECREF(keys);
        return PyErr_NoMemory();
    }
    for (i = 0; i < size; i++) {
        values[i] = NULL;
    }
    return new_dict(keys, values);
}
