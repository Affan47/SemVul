fileio_readall(fileio *self)
{
    PyObject *result;
    Py_ssize_t total = 0;
    Py_ssize_t n;

    if (self->fd < 0)
        return err_closed();
    if (!_PyVerify_fd(self->fd))
        return PyErr_SetFromErrno(PyExc_IOError);

    result = PyBytes_FromStringAndSize(NULL, SMALLCHUNK);
    if (result == NULL)
        return NULL;

    while (1) {
        size_t newsize = new_buffersize(self, total);
        if (newsize > PY_SSIZE_T_MAX || newsize <= 0) {
            PyErr_SetString(PyExc_OverflowError,
                "unbounded read returned more bytes "
                "than a Python string can hold ");
            Py_DECREF(result);
            return NULL;
        }

        if (PyBytes_GET_SIZE(result) < (Py_ssize_t)newsize) {
            if (_PyBytes_Resize(&result, newsize) < 0) {
                if (total == 0) {
                    Py_DECREF(result);
                    return NULL;
                }
                PyErr_Clear();
                break;
            }
        }
        Py_BEGIN_ALLOW_THREADS
        errno = 0;
        n = newsize - total;
#if defined(MS_WIN64) || defined(MS_WINDOWS)
        if (n > INT_MAX)
            n = INT_MAX;
        n = read(self->fd,
                 PyBytes_AS_STRING(result) + total,
                 (int)n);
#else
        n = read(self->fd,
                 PyBytes_AS_STRING(result) + total,
                 n);
#endif
        Py_END_ALLOW_THREADS
        if (n == 0)
            break;
        if (n < 0) {
            if (errno == EINTR) {
                if (PyErr_CheckSignals()) {
                    Py_DECREF(result);
                    return NULL;
                }
                continue;
            }
            if (total > 0)
                break;
            if (errno == EAGAIN) {
                Py_DECREF(result);
                Py_RETURN_NONE;
            }
            Py_DECREF(result);
            PyErr_SetFromErrno(PyExc_IOError);
            return NULL;
        }
        total += n;
    }

    if (PyBytes_GET_SIZE(result) > total) {
        if (_PyBytes_Resize(&result, total) < 0) {

            Py_DECREF(result);
            return NULL;
        }
    }
    return result;
}
