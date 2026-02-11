wrap_cmpfunc(PyObject *self, PyObject *args, void *wrapped)
{
    cmpfunc func = (cmpfunc)wrapped;
    int res;
    PyObject *other;

    if (!check_num_args(args, 1))
        return NULL;
    other = PyTuple_GET_ITEM(args, 0);
    if (Py_TYPE(other)->tp_compare != func &&
        !PyType_IsSubtype(Py_TYPE(other), Py_TYPE(self))) {
        PyErr_Format(
            PyExc_TypeError,
            "%s.__cmp__(x,y) requires y to be a '%s', not a '%s'",
            Py_TYPE(self)->tp_name,
            Py_TYPE(self)->tp_name,
            Py_TYPE(other)->tp_name);
        return NULL;
    }
    res = (*func)(self, other);
    if (PyErr_Occurred())
        return NULL;
    return PyInt_FromLong((long)res);
}
