func_set_kwdefaults(PyFunctionObject *op, PyObject *value)
{
    PyObject *tmp;

    if (value == Py_None)
        value = NULL;


    if (value != NULL && !PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
            "__kwdefaults__ must be set to a dict object");
        return -1;
    }
    tmp = op->func_kwdefaults;
    Py_XINCREF(value);
    op->func_kwdefaults = value;
    Py_XDECREF(tmp);
    return 0;
}
