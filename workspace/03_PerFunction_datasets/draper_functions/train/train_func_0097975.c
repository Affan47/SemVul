utf_16_le_decode(PyObject *self,
                 PyObject *args)
{
    Py_buffer pbuf;
    const char *errors = NULL;
    int byteorder = -1;
    int final = 0;
    Py_ssize_t consumed;
    PyObject *decoded = NULL;

    if (!PyArg_ParseTuple(args, "y*|zi:utf_16_le_decode",
                          &pbuf, &errors, &final))
        return NULL;

    consumed = pbuf.len;
    decoded = PyUnicode_DecodeUTF16Stateful(pbuf.buf, pbuf.len, errors,
        &byteorder, final ? NULL : &consumed);
    PyBuffer_Release(&pbuf);
    if (decoded == NULL)
        return NULL;
    return codec_tuple(decoded, consumed);
}
