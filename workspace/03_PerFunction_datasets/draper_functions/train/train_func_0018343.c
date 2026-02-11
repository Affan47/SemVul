posix_statvfs(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *keywords[] = {"path", NULL};
    path_t path;
    int result;
    PyObject *return_value = NULL;
    struct statvfs st;

    memset(&path, 0, sizeof(path));
    path.function_name = "statvfs";
#ifdef HAVE_FSTATVFS
    path.allow_fd = 1;
#endif
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O&:statvfs", keywords,
        path_converter, &path
        ))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
#ifdef HAVE_FSTATVFS
    if (path.fd != -1) {
#ifdef __APPLE__

        if (fstatvfs == NULL) {
            fd_specified("statvfs", path.fd);
            goto exit;
        }
#endif
        result = fstatvfs(path.fd, &st);
    }
    else
#endif
        result = statvfs(path.narrow, &st);
    Py_END_ALLOW_THREADS

    if (result) {
        return_value = path_error(&path);
        goto exit;
    }

    return_value = _pystatvfs_fromstructstatvfs(st);

exit:
    path_cleanup(&path);
    return return_value;
}
