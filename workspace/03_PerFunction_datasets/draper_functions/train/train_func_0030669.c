long_mul(PyLongObject *v, PyLongObject *w)
{
    PyLongObject *a, *b, *z;

    if (!convert_binop((PyObject *)v, (PyObject *)w, &a, &b)) {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    z = k_mul(a, b);

    if (((a->ob_size ^ b->ob_size) < 0) && z)
        z->ob_size = -(z->ob_size);
    Py_DECREF(a);
    Py_DECREF(b);
    return (PyObject *)z;
}
