os_access(PyModuleDef *module, PyObject *args, PyObject *kwargs)
{
    PyObject *return_value = NULL;
    static char *_keywords[] = {"path", "mode", "dir_fd", "effective_ids", "follow_symlinks", NULL};
    path_t path = PATH_T_INITIALIZE("access", 0, 1);
    int mode;
    int dir_fd = DEFAULT_DIR_FD;
    int effective_ids = 0;
    int follow_symlinks = 1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
        "O&i|$O&pp:access", _keywords,
        path_converter, &path, &mode, OS_STAT_DIR_FD_CONVERTER, &dir_fd, &effective_ids, &follow_symlinks))
        goto exit;
    return_value = os_access_impl(module, &path, mode, dir_fd, effective_ids, follow_symlinks);

exit:

    path_cleanup(&path);

    return return_value;
}
