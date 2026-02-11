load_long_binget(Unpicklerobject *self)
{
    PyObject *py_key = 0, *value = 0;
    unsigned char c;
    char *s;
    Py_ssize_t key;
    int rc;

    if (self->read_func(self, &s, 4) < 0) return -1;

    c = (unsigned char)s[0];
    key = (long)c;
    c = (unsigned char)s[1];
    key |= (long)c << 8;
    c = (unsigned char)s[2];
    key |= (long)c << 16;
    c = (unsigned char)s[3];
    key |= (long)c << 24;

    if (!( py_key = PyInt_FromLong((long)key)))  return -1;

    value = PyDict_GetItem(self->memo, py_key);
    if (! value) {
        PyErr_SetObject(BadPickleGet, py_key);
        rc = -1;
    }
    else {
        PDATA_APPEND(self->stack, value, -1);
        rc = 0;
    }

    Py_DECREF(py_key);
    return rc;
}
