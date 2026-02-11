signal_sigwaitinfo(PyObject *self, PyObject *args)
{
    PyObject *signals;
    sigset_t set;
    siginfo_t si;
    int err;

    if (!PyArg_ParseTuple(args, "O:sigwaitinfo", &signals))
        return NULL;

    if (iterable_to_sigset(signals, &set))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    err = sigwaitinfo(&set, &si);
    Py_END_ALLOW_THREADS
    if (err == -1)
        return PyErr_SetFromErrno(PyExc_OSError);

    return fill_siginfo(&si);
}
