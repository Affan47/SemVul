codec_encode(PyObject *self, PyObject *args)
{
    const char *encoding = NULL;
    const char *errors = NULL;
    PyObject *v;

    if (!PyArg_ParseTuple(args, "O|ss:encode", &v, &encoding, &errors))
        return NULL;

    if (encoding == NULL)
        encoding = PyUnicode_GetDefaultEncoding();


    return PyCodec_Encode(v, encoding, errors);
}
