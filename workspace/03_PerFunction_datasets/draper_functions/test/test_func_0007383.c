unicode_escape_encode(PyObject *self,
                     PyObject *args)
{
    PyObject *str, *v;
    const char *errors = NULL;

    if (!PyArg_ParseTuple(args, "O|z:unicode_escape_encode",
                          &str, &errors))
        return NULL;

    str = PyUnicode_FromObject(str);
    if (str == NULL || PyUnicode_READY(str) < 0) {
        Py_XDECREF(str);
        return NULL;
    }
    v = codec_tuple(PyUnicode_AsUnicodeEscapeString(str),
                    PyUnicode_GET_LENGTH(str));
    Py_DECREF(str);
    return v;
}
