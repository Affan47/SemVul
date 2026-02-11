posix_writev(PyObject *self, PyObject *args)
{
    int fd, cnt;
    Py_ssize_t res;
    PyObject *seq;
    struct iovec *iov;
    Py_buffer *buf;
    if (!PyArg_ParseTuple(args, "iO:writev", &fd, &seq))
        return NULL;
    if (!PySequence_Check(seq)) {
        PyErr_SetString(PyExc_TypeError,
            "writev() arg 2 must be a sequence");
        return NULL;
    }
    cnt = PySequence_Size(seq);

    if (!iov_setup(&iov, &buf, seq, cnt, PyBUF_SIMPLE)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    res = writev(fd, iov, cnt);
    Py_END_ALLOW_THREADS

    iov_cleanup(iov, buf, cnt);
    return PyLong_FromSsize_t(res);
}
