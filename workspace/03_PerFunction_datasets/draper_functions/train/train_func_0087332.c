func_set_dict(PyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;

    if (restricted())
        return -1;

    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError,
                        "function's dictionary may not be deleted");
        return -1;
    }

    if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "setting function's dictionary to a non-dict");
        return -1;
    }
    tmp = op->func_dict;
    Py_INCREF(value);
    op->func_dict = value;
    Py_XDECREF(tmp);
    return 0;
}
