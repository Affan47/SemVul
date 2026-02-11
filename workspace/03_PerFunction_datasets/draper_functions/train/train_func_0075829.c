PyTuple_SetItem(PyObject *op, Py_ssize_t i, PyObject *newitem)
{
    PyObject *olditem;
    PyObject **p;
    if (!PyTuple_Check(op) || op->ob_refcnt != 1) {
        Py_XDECREF(newitem);
        PyErr_BadInternalCall();
        return -1;
    }
    if (i < 0 || i >= Py_SIZE(op)) {
        Py_XDECREF(newitem);
        PyErr_SetString(PyExc_IndexError,
                        "tuple assignment index out of range");
        return -1;
    }
    p = ((PyTupleObject *)op) -> ob_item + i;
    olditem = *p;
    *p = newitem;
    Py_XDECREF(olditem);
    return 0;
}
