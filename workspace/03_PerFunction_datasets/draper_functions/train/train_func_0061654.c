charmap_encode(PyObject *self,
             PyObject *args)
{
    PyObject *str, *v;
    const char *errors = NULL;
    PyObject *mapping = NULL;

    if (!PyArg_ParseTuple(args, "O|zO:charmap_encode",
                          &str, &errors, &mapping))
        return NULL;
    if (mapping == Py_None)
        mapping = NULL;

    str = PyUnicode_FromObject(str);
    if (str == NULL)
        return NULL;
    v = codec_tuple(PyUnicode_EncodeCharmap(
                               PyUnicode_AS_UNICODE(str),
                               PyUnicode_GET_SIZE(str),
                               mapping,
                               errors),
                    PyUnicode_GET_SIZE(str));
    Py_DECREF(str);
    return v;
}
