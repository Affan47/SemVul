subprocess_cloexec_pipe(PyObject *self, PyObject *noargs)
{
    int fds[2];
    int res;
#ifdef HAVE_PIPE2
    Py_BEGIN_ALLOW_THREADS
    res = pipe2(fds, O_CLOEXEC);
    Py_END_ALLOW_THREADS
    if (res != 0 && errno == ENOSYS)
    {
        {
#endif


        long oldflags;

        res = pipe(fds);

        if (res == 0) {
            oldflags = fcntl(fds[0], F_GETFD, 0);
            if (oldflags < 0) res = oldflags;
        }
        if (res == 0)
            res = fcntl(fds[0], F_SETFD, oldflags | FD_CLOEXEC);

        if (res == 0) {
            oldflags = fcntl(fds[1], F_GETFD, 0);
            if (oldflags < 0) res = oldflags;
        }
        if (res == 0)
            res = fcntl(fds[1], F_SETFD, oldflags | FD_CLOEXEC);
#ifdef HAVE_PIPE2
        }
    }
#endif
    if (res != 0)
        return PyErr_SetFromErrno(PyExc_OSError);
    return Py_BuildValue("(ii)", fds[0], fds[1]);
}
