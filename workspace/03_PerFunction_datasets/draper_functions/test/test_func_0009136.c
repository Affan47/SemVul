posix_mkdir(PyObject *self, PyObject *args)
{
    int res;
    const char *path;
    int mode = 0777;

#ifdef MS_WINDOWS
    PyObject *po;
    if (PyArg_ParseTuple(args, "U|i:mkdir", &po, &mode))
    {
        wchar_t *wpath = PyUnicode_AsUnicode(po);
        if (wpath == NULL)
            return NULL;

        Py_BEGIN_ALLOW_THREADS
        res = CreateDirectoryW(wpath, NULL);
        Py_END_ALLOW_THREADS
        if (!res)
            return win32_error_object("mkdir", po);
        Py_INCREF(Py_None);
        return Py_None;
    }


    PyErr_Clear();
    if (!PyArg_ParseTuple(args, "y|i:mkdir", &path, &mode))
        return NULL;
    if (win32_warn_bytes_api())
        return NULL;
    Py_BEGIN_ALLOW_THREADS
    res = CreateDirectoryA(path, NULL);
    Py_END_ALLOW_THREADS
    if (!res) {
        win32_error("mkdir", path);
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
#else
    PyObject *opath;

    if (!PyArg_ParseTuple(args, "O&|i:mkdir",
                          PyUnicode_FSConverter, &opath, &mode))
        return NULL;
    path = PyBytes_AsString(opath);
    Py_BEGIN_ALLOW_THREADS
#if ( defined(__WATCOMC__) || defined(PYCC_VACPP) ) && !defined(__QNX__)
    res = mkdir(path);
#else
    res = mkdir(path, mode);
#endif
    Py_END_ALLOW_THREADS
    if (res < 0)
        return posix_error_with_allocated_filename(opath);
    Py_DECREF(opath);
    Py_INCREF(Py_None);
    return Py_None;
#endif
}
