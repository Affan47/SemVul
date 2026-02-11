posix_tcsetpgrp(PyObject *self, PyObject *args)
{
    int fd;
    pid_t pgid;
    if (!PyArg_ParseTuple(args, "i" _Py_PARSE_PID ":tcsetpgrp", &fd, &pgid))
        return NULL;
    if (tcsetpgrp(fd, pgid) < 0)
        return posix_error();
    Py_INCREF(Py_None);
    return Py_None;
}
