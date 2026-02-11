_PyErr_ChainExceptions(PyObject *exc, PyObject *val, PyObject *tb)
{
    if (exc == NULL)
        return;

    if (PyErr_Occurred()) {
        PyObject *exc2, *val2, *tb2;
        PyErr_Fetch(&exc2, &val2, &tb2);
        PyErr_NormalizeException(&exc, &val, &tb);
        Py_DECREF(exc);
        Py_XDECREF(tb);
        PyErr_NormalizeException(&exc2, &val2, &tb2);
        PyException_SetContext(val2, val);
        PyErr_Restore(exc2, val2, tb2);
    }
    else {
        PyErr_Restore(exc, val, tb);
    }
}
