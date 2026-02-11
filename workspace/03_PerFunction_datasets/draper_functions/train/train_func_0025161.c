textiowrapper_get_decoded_chars(textio *self, Py_ssize_t n)
{
    PyObject *chars;
    Py_ssize_t avail;

    if (self->decoded_chars == NULL)
        return PyUnicode_FromStringAndSize(NULL, 0);

    avail = (PyUnicode_GET_SIZE(self->decoded_chars)
             - self->decoded_chars_used);

    assert(avail >= 0);

    if (n < 0 || n > avail)
        n = avail;

    if (self->decoded_chars_used > 0 || n < avail) {
        chars = PyUnicode_FromUnicode(
            PyUnicode_AS_UNICODE(self->decoded_chars)
            + self->decoded_chars_used, n);
        if (chars == NULL)
            return NULL;
    }
    else {
        chars = self->decoded_chars;
        Py_INCREF(chars);
    }

    self->decoded_chars_used += n;
    return chars;
}
