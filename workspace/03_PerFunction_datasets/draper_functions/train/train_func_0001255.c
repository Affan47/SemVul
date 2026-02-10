call_maybe(PyObject *o, _Py_Identifier *nameid, char *format, ...)
{
    va_list va;
    PyObject *args, *func = 0, *retval;
    va_start(va, format);

    func = lookup_maybe(o, nameid);
    if (func == NULL) {
        va_end(va);
        if (!PyErr_Occurred())
            Py_RETURN_NOTIMPLEMENTED;
        return NULL;
    }

    if (format && *format)
        args = Py_VaBuildValue(format, va);
    else
        args = PyTuple_New(0);

    va_end(va);

    if (args == NULL)
        return NULL;

    assert(PyTuple_Check(args));
    retval = PyObject_Call(func, args, NULL);

    Py_DECREF(args);
    Py_DECREF(func);

    return retval;
}
