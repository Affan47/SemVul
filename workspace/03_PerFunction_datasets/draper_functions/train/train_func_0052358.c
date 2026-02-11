Q_get(void *ptr, Py_ssize_t size)
{
    unsigned PY_LONG_LONG val;
    memcpy(&val, ptr, sizeof(val));
    GET_BITFIELD(val, size);
    return PyLong_FromUnsignedLongLong(val);
}
