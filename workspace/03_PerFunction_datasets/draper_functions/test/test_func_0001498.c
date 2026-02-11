mmap_write_method(mmap_object *self,
                  PyObject *args)
{
    Py_ssize_t length;
    char *data;

    CHECK_VALID(NULL);
    if (!PyArg_ParseTuple(args, "y#:write", &data, &length))
        return(NULL);

    if (!is_writable(self))
        return NULL;

    if ((self->pos + length) > self->size) {
        PyErr_SetString(PyExc_ValueError, "data out of range");
        return NULL;
    }
    memcpy(self->data+self->pos, data, length);
    self->pos = self->pos+length;
    Py_INCREF(Py_None);
    return Py_None;
}
