tupleconcat(PyTupleObject *a, PyObject *bb)
{
    Py_ssize_t size;
    Py_ssize_t i;
    PyObject **src, **dest;
    PyTupleObject *np;
    if (!PyTuple_Check(bb)) {
        PyErr_Format(PyExc_TypeError,
             "can only concatenate tuple (not \"%.200s\") to tuple",
                 Py_TYPE(bb)->tp_name);
        return NULL;
    }
#define b ((PyTupleObject *)bb)
    size = Py_SIZE(a) + Py_SIZE(b);
    if (size < 0)
        return PyErr_NoMemory();
    np = (PyTupleObject *) PyTuple_New(size);
    if (np == NULL) {
        return NULL;
    }
    src = a->ob_item;
    dest = np->ob_item;
    for (i = 0; i < Py_SIZE(a); i++) {
        PyObject *v = src[i];
        Py_INCREF(v);
        dest[i] = v;
    }
    src = b->ob_item;
    dest = np->ob_item + Py_SIZE(a);
    for (i = 0; i < Py_SIZE(b); i++) {
        PyObject *v = src[i];
        Py_INCREF(v);
        dest[i] = v;
    }
    return (PyObject *)np;
#undef b
}
