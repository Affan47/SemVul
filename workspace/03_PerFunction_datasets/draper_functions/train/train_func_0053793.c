callback_func0 ()
{
    PyObject *py_arg = arguments ? Py_BuildValue ("(O)",arguments) : NULL;
    PyObject* val = make_call (py_arg);
    Py_XDECREF (val);
}
