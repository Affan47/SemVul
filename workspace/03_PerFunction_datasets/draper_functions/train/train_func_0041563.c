load_short_binbytes(UnpicklerObject *self)
{
    PyObject *bytes;
    Py_ssize_t x;
    char *s;

    if (_Unpickler_Read(self, &s, 1) < 0)
        return -1;

    x = (unsigned char)s[0];

    if (_Unpickler_Read(self, &s, x) < 0)
        return -1;

    bytes = PyBytes_FromStringAndSize(s, x);
    if (bytes == NULL)
        return -1;

    PDATA_PUSH(self->stack, bytes, -1);
    return 0;
}
