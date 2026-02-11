signaldict_setitem(PyObject *self, PyObject *key, PyObject *value)
{
    uint32_t flag;
    int x;

    if (value == NULL) {
        return value_error_int("signal keys cannot be deleted");
    }

    flag = exception_as_flag(key);
    if (flag & DEC_ERRORS) {
        return -1;
    }

    x = PyObject_IsTrue(value);
    if (x < 0) {
        return -1;
    }

    if (x == 1) {
        SdFlags(self) |= flag;
    }
    else {
        SdFlags(self) &= ~flag;
    }

    return 0;
}
