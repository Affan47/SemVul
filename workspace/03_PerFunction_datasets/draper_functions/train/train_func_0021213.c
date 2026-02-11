posix_truncate(PyObject *self, PyObject *args)
{
    PyObject *opath;
    const char *path;
    off_t length;
    int res;

    if (!PyArg_ParseTuple(args, "O&O&:truncate",
            PyUnicode_FSConverter, &opath, _parse_off_t, &length))
        return NULL;
    path = PyBytes_AsString(opath);

    Py_BEGIN_ALLOW_THREADS
    res = truncate(path, length);
    Py_END_ALLOW_THREADS
    Py_DECREF(opath);
    if (res < 0)
        return posix_error();
    Py_RETURN_NONE;
}
