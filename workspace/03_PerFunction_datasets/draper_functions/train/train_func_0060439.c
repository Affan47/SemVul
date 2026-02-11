bytesio_read(bytesio *self, PyObject *args)
{
    Py_ssize_t size, n;
    char *output;
    PyObject *arg = Py_None;

    CHECK_CLOSED(self);

    if (!PyArg_ParseTuple(args, "|O:read", &arg))
        return NULL;

    if (PyNumber_Check(arg)) {
        size = PyNumber_AsSsize_t(arg, PyExc_OverflowError);
        if (size == -1 && PyErr_Occurred())
            return NULL;
    }
    else if (arg == Py_None) {

        size = -1;
    }
    else {
        PyErr_Format(PyExc_TypeError, "integer argument expected, got '%s'",
                     Py_TYPE(arg)->tp_name);
        return NULL;
    }


    n = self->string_size - self->pos;
    if (size < 0 || size > n) {
        size = n;
        if (size < 0)
            size = 0;
    }

    assert(self->buf != NULL);
    output = self->buf + self->pos;
    self->pos += size;

    return PyBytes_FromStringAndSize(output, size);
}
