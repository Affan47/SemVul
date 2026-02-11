_PyIOBase_check_seekable(PyObject *self, PyObject *args)
{
    PyObject *res  = PyObject_CallMethodObjArgs(self, _PyIO_str_seekable, NULL);
    if (res == NULL)
        return NULL;
    if (res != Py_True) {
        Py_CLEAR(res);
        PyErr_SetString(PyExc_IOError, "File or stream is not seekable.");
        return NULL;
    }
    if (args == Py_True) {
        Py_DECREF(res);
    }
    return res;
}
