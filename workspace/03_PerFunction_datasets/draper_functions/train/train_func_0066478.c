blockingioerror_init(PyBlockingIOErrorObject *self, PyObject *args,
                     PyObject *kwds)
{
    PyObject *myerrno = NULL, *strerror = NULL;
    PyObject *baseargs = NULL;
    Py_ssize_t written = 0;

    assert(PyTuple_Check(args));

    self->written = 0;
    if (!PyArg_ParseTuple(args, "OO|n:BlockingIOError",
                          &myerrno, &strerror, &written))
        return -1;

    baseargs = PyTuple_Pack(2, myerrno, strerror);
    if (baseargs == NULL)
        return -1;

    if (((PyTypeObject *)PyExc_IOError)->tp_init(
                (PyObject *)self, baseargs, kwds) == -1) {
        Py_DECREF(baseargs);
        return -1;
    }
    Py_DECREF(baseargs);

    self->written = written;
    return 0;
}
