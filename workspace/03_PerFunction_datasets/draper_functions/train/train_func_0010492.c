sock_getsockopt(PySocketSockObject *s, PyObject *args)
{
    int level;
    int optname;
    int res;
    PyObject *buf;
    socklen_t buflen = 0;

    if (!PyArg_ParseTuple(args, "ii|i:getsockopt",
                          &level, &optname, &buflen))
        return NULL;

    if (buflen == 0) {
        int flag = 0;
        socklen_t flagsize = sizeof flag;
        res = getsockopt(s->sock_fd, level, optname,
                         (void *)&flag, &flagsize);
        if (res < 0)
            return s->errorhandler();
        return PyLong_FromLong(flag);
    }
#ifdef __VMS


    if (buflen > 1024) {
#else
    if (buflen <= 0 || buflen > 1024) {
#endif
        PyErr_SetString(PyExc_OSError,
                        "getsockopt buflen out of range");
        return NULL;
    }
    buf = PyBytes_FromStringAndSize((char *)NULL, buflen);
    if (buf == NULL)
        return NULL;
    res = getsockopt(s->sock_fd, level, optname,
                     (void *)PyBytes_AS_STRING(buf), &buflen);
    if (res < 0) {
        Py_DECREF(buf);
        return s->errorhandler();
    }
    _PyBytes_Resize(&buf, buflen);
    return buf;
}
