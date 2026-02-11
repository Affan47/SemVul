time_gmtime(PyObject *self, PyObject *args)
{
    time_t when;
    struct tm buf, *local;

    if (!parse_time_t_args(args, "|O:gmtime", &when))
        return NULL;

    errno = 0;
    local = gmtime(&when);
    if (local == NULL) {
#ifdef EINVAL
        if (errno == 0)
            errno = EINVAL;
#endif
        return PyErr_SetFromErrno(PyExc_OSError);
    }
    buf = *local;
    return tmtotuple(&buf);
}
