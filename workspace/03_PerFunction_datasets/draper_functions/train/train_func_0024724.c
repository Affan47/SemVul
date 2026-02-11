bytearray_contains(PyObject *self, PyObject *arg)
{
    Py_ssize_t ival = PyNumber_AsSsize_t(arg, PyExc_ValueError);
    if (ival == -1 && PyErr_Occurred()) {
        Py_buffer varg;
        int pos;
        PyErr_Clear();
        if (_getbuffer(arg, &varg) < 0)
            return -1;
        pos = stringlib_find(PyByteArray_AS_STRING(self), Py_SIZE(self),
                             varg.buf, varg.len, 0);
        PyBuffer_Release(&varg);
        return pos >= 0;
    }
    if (ival < 0 || ival >= 256) {
        PyErr_SetString(PyExc_ValueError, "byte must be in range(0, 256)");
        return -1;
    }

    return memchr(PyByteArray_AS_STRING(self), ival, Py_SIZE(self)) != NULL;
}
