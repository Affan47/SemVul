oss_read(oss_audio_t *self, PyObject *args)
{
    int size, count;
    char *cp;
    PyObject *rv;

    if (!_is_fd_valid(self->fd))
        return NULL;

    if (!PyArg_ParseTuple(args, "i:read", &size))
        return NULL;
    rv = PyBytes_FromStringAndSize(NULL, size);
    if (rv == NULL)
        return NULL;
    cp = PyBytes_AS_STRING(rv);

    Py_BEGIN_ALLOW_THREADS
    count = read(self->fd, cp, size);
    Py_END_ALLOW_THREADS

    if (count < 0) {
        PyErr_SetFromErrno(PyExc_IOError);
        Py_DECREF(rv);
        return NULL;
    }
    self->icount += count;
    _PyBytes_Resize(&rv, count);
    return rv;
}
