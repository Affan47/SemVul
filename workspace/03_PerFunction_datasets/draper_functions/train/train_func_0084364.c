long_divmod(PyObject *v, PyObject *w)
{
    PyLongObject *a, *b, *div, *mod;
    PyObject *z;

    CONVERT_BINOP(v, w, &a, &b);

    if (l_divmod(a, b, &div, &mod) < 0) {
        Py_DECREF(a);
        Py_DECREF(b);
        return NULL;
    }
    z = PyTuple_New(2);
    if (z != NULL) {
        PyTuple_SetItem(z, 0, (PyObject *) div);
        PyTuple_SetItem(z, 1, (PyObject *) mod);
    }
    else {
        Py_DECREF(div);
        Py_DECREF(mod);
    }
    Py_DECREF(a);
    Py_DECREF(b);
    return z;
}
