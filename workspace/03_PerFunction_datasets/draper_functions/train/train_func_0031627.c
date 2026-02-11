wrap_coercefunc(PyObject *self, PyObject *args, void *wrapped)
{
    coercion func = (coercion)wrapped;
    PyObject *other, *res;
    int ok;

    if (!check_num_args(args, 1))
        return NULL;
    other = PyTuple_GET_ITEM(args, 0);
    ok = func(&self, &other);
    if (ok < 0)
        return NULL;
    if (ok > 0) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }
    res = PyTuple_New(2);
    if (res == NULL) {
        Py_DECREF(self);
        Py_DECREF(other);
        return NULL;
    }
    PyTuple_SET_ITEM(res, 0, self);
    PyTuple_SET_ITEM(res, 1, other);
    return res;
}
