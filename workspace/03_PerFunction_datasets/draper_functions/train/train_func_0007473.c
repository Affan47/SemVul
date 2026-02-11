import_from(PyObject *v, PyObject *name)
{
    PyObject *x;

    x = PyObject_GetAttr(v, name);
    if (x == NULL && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError, "cannot import name %R", name);
    }
    return x;
}
