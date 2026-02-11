posix_readlink(PyObject *self, PyObject *args)
{
    PyObject* v;
    char buf[MAXPATHLEN];
    PyObject *opath;
    char *path;
    int n;
    int arg_is_unicode = 0;

    if (!PyArg_ParseTuple(args, "O&:readlink",
                          PyUnicode_FSConverter, &opath))
        return NULL;
    path = PyBytes_AsString(opath);
    v = PySequence_GetItem(args, 0);
    if (v == NULL) {
        Py_DECREF(opath);
        return NULL;
    }

    if (PyUnicode_Check(v)) {
        arg_is_unicode = 1;
    }
    Py_DECREF(v);

    Py_BEGIN_ALLOW_THREADS
    n = readlink(path, buf, (int) sizeof buf);
    Py_END_ALLOW_THREADS
    if (n < 0)
        return posix_error_with_allocated_filename(opath);

    Py_DECREF(opath);
    if (arg_is_unicode)
        return PyUnicode_DecodeFSDefaultAndSize(buf, n);
    else
        return PyBytes_FromStringAndSize(buf, n);
}
