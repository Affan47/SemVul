unicode_buffer_getreadbuf(PyUnicodeObject *self,
                          Py_ssize_t index,
                          const void **ptr)
{
    if (index != 0) {
        PyErr_SetString(PyExc_SystemError,
                        "accessing non-existent unicode segment");
        return -1;
    }
    *ptr = (void *) self->str;
    return PyUnicode_GET_DATA_SIZE(self);
}
