load_counted_long(UnpicklerObject *self, int size)
{
    PyObject *value;
    char *nbytes;
    char *pdata;

    assert(size == 1 || size == 4);
    if (_Unpickler_Read(self, &nbytes, size) < 0)
        return -1;

    size = calc_binint(nbytes, size);
    if (size < 0) {

        PyErr_SetString(UnpicklingError,
                        "LONG pickle has negative byte count");
        return -1;
    }

    if (size == 0)
        value = PyLong_FromLong(0L);
    else {

        if (_Unpickler_Read(self, &pdata, size) < 0)
            return -1;
        value = _PyLong_FromByteArray((unsigned char *)pdata, (size_t)size,
                                      1  , 1  );
    }
    if (value == NULL)
        return -1;
    PDATA_PUSH(self->stack, value, -1);
    return 0;
}
