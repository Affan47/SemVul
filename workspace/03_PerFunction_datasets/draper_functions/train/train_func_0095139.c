realize(stringio *self)
{
    Py_ssize_t len;
    PyObject *intermediate;

    if (self->state == STATE_REALIZED)
        return 0;
    assert(self->state == STATE_ACCUMULATING);
    self->state = STATE_REALIZED;

    intermediate = _PyAccu_Finish(&self->accu);
    if (intermediate == NULL)
        return -1;


    len = PyUnicode_GET_LENGTH(intermediate);
    if (resize_buffer(self, len) < 0) {
        Py_DECREF(intermediate);
        return -1;
    }
    if (!PyUnicode_AsUCS4(intermediate, self->buf, len, 0)) {
        Py_DECREF(intermediate);
        return -1;
    }

    Py_DECREF(intermediate);
    return 0;
}
