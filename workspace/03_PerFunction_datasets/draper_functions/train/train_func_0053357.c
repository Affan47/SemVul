date_format(PyDateTime_Date *self, PyObject *args)
{
    PyObject *format;

    if (!PyArg_ParseTuple(args, "U:__format__", &format))
        return NULL;


    if (PyUnicode_GetLength(format) == 0)
        return PyObject_Str((PyObject *)self);

    return _PyObject_CallMethodId((PyObject *)self, &PyId_strftime, "O", format);
}
