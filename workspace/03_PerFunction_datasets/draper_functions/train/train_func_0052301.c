islt(PyObject *x, PyObject *y, PyObject *compare)
{
    PyObject *res;
    PyObject *args;
    Py_ssize_t i;

    assert(compare != NULL);


    args = PyTuple_New(2);
    if (args == NULL)
        return -1;
    Py_INCREF(x);
    Py_INCREF(y);
    PyTuple_SET_ITEM(args, 0, x);
    PyTuple_SET_ITEM(args, 1, y);
    res = PyObject_Call(compare, args, NULL);
    Py_DECREF(args);
    if (res == NULL)
        return -1;
    if (!PyInt_Check(res)) {
        PyErr_Format(PyExc_TypeError,
                     "comparison function must return int, not %.200s",
                     res->ob_type->tp_name);
        Py_DECREF(res);
        return -1;
    }
    i = PyInt_AsLong(res);
    Py_DECREF(res);
    return i < 0;
}
