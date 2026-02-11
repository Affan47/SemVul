posix_mkfifo(PyObject *self, PyObject *args)
{
    PyObject *opath;
    char *filename;
    int mode = 0666;
    int res;
    if (!PyArg_ParseTuple(args, "O&|i:mkfifo", PyUnicode_FSConverter, &opath,
                          &mode))
        return NULL;
    filename = PyBytes_AS_STRING(opath);
    Py_BEGIN_ALLOW_THREADS
    res = mkfifo(filename, mode);
    Py_END_ALLOW_THREADS
    Py_DECREF(opath);
    if (res < 0)
        return posix_error();
    Py_INCREF(Py_None);
    return Py_None;
}
