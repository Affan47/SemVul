method_is_overloaded(PyObject *left, PyObject *right, struct _Py_Identifier *name)
{
    PyObject *a, *b;
    int ok;

    b = _PyObject_GetAttrId((PyObject *)(Py_TYPE(right)), name);
    if (b == NULL) {
        PyErr_Clear();

        return 0;
    }

    a = _PyObject_GetAttrId((PyObject *)(Py_TYPE(left)), name);
    if (a == NULL) {
        PyErr_Clear();
        Py_DECREF(b);

        return 1;
    }

    ok = PyObject_RichCompareBool(a, b, Py_NE);
    Py_DECREF(a);
    Py_DECREF(b);
    if (ok < 0) {
        PyErr_Clear();
        return 0;
    }

    return ok;
}
