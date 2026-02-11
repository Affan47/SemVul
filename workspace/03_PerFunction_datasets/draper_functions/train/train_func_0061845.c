fileio_isatty(fileio *self)
{
    long res;

    if (self->fd < 0)
        return err_closed();
    Py_BEGIN_ALLOW_THREADS
    res = isatty(self->fd);
    Py_END_ALLOW_THREADS
    return PyBool_FromLong(res);
}
