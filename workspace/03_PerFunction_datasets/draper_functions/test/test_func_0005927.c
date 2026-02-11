long_neg(PyLongObject *v)
{
    PyLongObject *z;
    if (v->ob_size == 0 && PyLong_CheckExact(v)) {

        Py_INCREF(v);
        return (PyObject *) v;
    }
    z = (PyLongObject *)_PyLong_Copy(v);
    if (z != NULL)
        z->ob_size = -(v->ob_size);
    return (PyObject *)z;
}
