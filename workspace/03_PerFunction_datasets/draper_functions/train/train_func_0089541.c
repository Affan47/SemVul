set_progress_callback(PyObject *self, PyObject *args)
{
    PyObject *callback;

    if (PyArg_ParseTuple(args, "O:set_progress_callback", &callback))
    {
        if (!PyCallable_Check(callback))
        {
            PyErr_SetString(PyExc_TypeError, "Expected a callback function");
            return NULL;
        }

        Py_XINCREF(callback);

        Py_XDECREF(progress_callback);

        progress_callback = callback;
    }

    Py_INCREF(Py_None);
    return Py_None;
}
