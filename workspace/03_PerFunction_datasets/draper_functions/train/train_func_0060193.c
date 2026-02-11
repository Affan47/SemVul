binascii_crc32(PyObject *self, PyObject *args)
{
    unsigned int crc32val = 0;
    Py_buffer pbuf;
    Byte *buf;
    Py_ssize_t len;
    int signed_val;

    if (!PyArg_ParseTuple(args, "y*|I:crc32", &pbuf, &crc32val))
    return NULL;
    buf = (Byte*)pbuf.buf;
    len = pbuf.len;
    signed_val = crc32(crc32val, buf, len);
    PyBuffer_Release(&pbuf);
    return PyLong_FromUnsignedLong(signed_val & 0xffffffffU);
}
