slice_indices(PyObject *self, PyObject *args)
{
    PyObject *ret, *key, *tmp;
    Py_ssize_t s[4];
    Py_ssize_t i, len;

    if (!PyArg_ParseTuple(args, "On", &key, &len)) {
        return NULL;
    }
    if (!PySlice_Check(key)) {
        PyErr_SetString(PyExc_TypeError,
            "first argument must be a slice object");
        return NULL;
    }
    if (PySlice_GetIndicesEx(key, len, &s[0], &s[1], &s[2], &s[3]) < 0) {
        return NULL;
    }

    ret = PyTuple_New(4);
    if (ret == NULL)
        return NULL;

    for (i = 0; i < 4; i++) {
        tmp = PyLong_FromSsize_t(s[i]);
        if (tmp == NULL)
            goto error;
        PyTuple_SET_ITEM(ret, i, tmp);
    }

    return ret;

error:
    Py_DECREF(ret);
    return NULL;
}
