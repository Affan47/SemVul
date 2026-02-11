half_compare(PyObject *self, PyObject *other)
{
    PyObject *func, *args, *res;
    static PyObject *cmp_str;
    Py_ssize_t c;

    func = lookup_method(self, "__cmp__", &cmp_str);
    if (func == NULL) {
        PyErr_Clear();
    }
    else {
        args = PyTuple_Pack(1, other);
        if (args == NULL)
            res = NULL;
        else {
            res = PyObject_Call(func, args, NULL);
            Py_DECREF(args);
        }
        Py_DECREF(func);
        if (res != Py_NotImplemented) {
            if (res == NULL)
                return -2;
            c = PyInt_AsLong(res);
            Py_DECREF(res);
            if (c == -1 && PyErr_Occurred())
                return -2;
            return (c < 0) ? -1 : (c > 0) ? 1 : 0;
        }
        Py_DECREF(res);
    }
    return 2;
}
