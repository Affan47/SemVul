set_difference_multi(PySetObject *so, PyObject *args)
{
    Py_ssize_t i;
    PyObject *result, *other;

    if (PyTuple_GET_SIZE(args) == 0)
        return set_copy(so);

    other = PyTuple_GET_ITEM(args, 0);
    result = set_difference(so, other);
    if (result == NULL)
        return NULL;

    for (i=1 ; i<PyTuple_GET_SIZE(args) ; i++) {
        other = PyTuple_GET_ITEM(args, i);
        if (set_difference_update_internal((PySetObject *)result, other) == -1) {
            Py_DECREF(result);
            return NULL;
        }
    }
    return result;
}
