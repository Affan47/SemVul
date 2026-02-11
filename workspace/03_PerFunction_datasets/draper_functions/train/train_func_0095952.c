utf_16_le_encode(PyObject *self,
                 PyObject *args)
{
    PyObject *str, *v;
    const char *errors = NULL;

    if (!PyArg_ParseTuple(args, "O|z:utf_16_le_encode",
                          &str, &errors))
        return NULL;

    str = PyUnicode_FromObject(str);
    if (str == NULL)
        return NULL;
    v = codec_tuple(PyUnicode_EncodeUTF16(PyUnicode_AS_UNICODE(str),
                                             PyUnicode_GET_SIZE(str),
                                             errors,
                                             -1),
                       PyUnicode_GET_SIZE(str));
    Py_DECREF(str);
    return v;
}
