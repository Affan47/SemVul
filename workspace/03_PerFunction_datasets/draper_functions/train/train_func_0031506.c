posix_mknod(PyObject *self, PyObject *args, PyObject *kwargs)
{
    path_t path;
    int mode = 0666;
    dev_t device = 0;
    int dir_fd = DEFAULT_DIR_FD;
    int result;
    PyObject *return_value = NULL;
    static char *keywords[] = {"path", "mode", "device", "dir_fd", NULL};

    memset(&path, 0, sizeof(path));
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O&|iO&$O&:mknod", keywords,
        path_converter, &path,
        &mode, _Py_Dev_Converter, &device,
#ifdef HAVE_MKNODAT
        dir_fd_converter, &dir_fd
#else
        dir_fd_unavailable, &dir_fd
#endif
        ))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
#ifdef HAVE_MKNODAT
    if (dir_fd != DEFAULT_DIR_FD)
        result = mknodat(dir_fd, path.narrow, mode, device);
    else
#endif
        result = mknod(path.narrow, mode, device);
    Py_END_ALLOW_THREADS

    if (result < 0) {
        return_value = posix_error();
        goto exit;
    }

    return_value = Py_None;
    Py_INCREF(Py_None);

exit:
    path_cleanup(&path);
    return return_value;
}
