posix_initgroups(PyObject *self, PyObject *args)
{
    PyObject *oname;
    char *username;
    int res;
    long gid;

    if (!PyArg_ParseTuple(args, "O&l:initgroups",
                          PyUnicode_FSConverter, &oname, &gid))
        return NULL;
    username = PyBytes_AS_STRING(oname);

    res = initgroups(username, (gid_t) gid);
    Py_DECREF(oname);
    if (res == -1)
        return PyErr_SetFromErrno(PyExc_OSError);

    Py_INCREF(Py_None);
    return Py_None;
}
