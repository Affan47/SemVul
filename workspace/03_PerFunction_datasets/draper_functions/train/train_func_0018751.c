posix_chown(PyObject *self, PyObject *args)
{
    PyObject *opath;
    char *path;
    long uid, gid;
    int res;
    if (!PyArg_ParseTuple(args, "O&ll:chown",
                          PyUnicode_FSConverter, &opath,
                          &uid, &gid))
        return NULL;
    path = PyBytes_AsString(opath);
    Py_BEGIN_ALLOW_THREADS
    res = chown(path, (uid_t) uid, (gid_t) gid);
    Py_END_ALLOW_THREADS
    if (res < 0)
        return posix_error_with_allocated_filename(opath);
    Py_DECREF(opath);
    Py_INCREF(Py_None);
    return Py_None;
}
