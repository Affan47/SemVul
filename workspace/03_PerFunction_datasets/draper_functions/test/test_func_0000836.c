sock_shutdown(PySocketSockObject *s, PyObject *arg)
{
    int how;
    int res;

    how = PyLong_AsLong(arg);
    if (how == -1 && PyErr_Occurred())
        return NULL;
    Py_BEGIN_ALLOW_THREADS
    res = shutdown(s->sock_fd, how);
    Py_END_ALLOW_THREADS
    if (res < 0)
        return s->errorhandler();
    Py_INCREF(Py_None);
    return Py_None;
}
