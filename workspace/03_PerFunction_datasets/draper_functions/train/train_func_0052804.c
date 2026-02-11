socket_CMSG_SPACE(PyObject *self, PyObject *args)
{
    Py_ssize_t length;
    size_t result;

    if (!PyArg_ParseTuple(args, "n:CMSG_SPACE", &length))
        return NULL;
    if (length < 0 || !get_CMSG_SPACE(length, &result)) {
        PyErr_SetString(PyExc_OverflowError,
                        "CMSG_SPACE() argument out of range");
        return NULL;
    }
    return PyLong_FromSize_t(result);
}
