os_access_impl(PyModuleDef *module, path_t *path, int mode, int dir_fd, int effective_ids, int follow_symlinks)

{
    PyObject *return_value = NULL;

#ifdef MS_WINDOWS
    DWORD attr;
#else
    int result;
#endif

#ifndef HAVE_FACCESSAT
    if (follow_symlinks_specified("access", follow_symlinks))
        goto exit;

    if (effective_ids) {
        argument_unavailable_error("access", "effective_ids");
        goto exit;
    }
#endif

#ifdef MS_WINDOWS
    Py_BEGIN_ALLOW_THREADS
    if (path->wide != NULL)
        attr = GetFileAttributesW(path->wide);
    else
        attr = GetFileAttributesA(path->narrow);
    Py_END_ALLOW_THREADS


    return_value = PyBool_FromLong(
        (attr != INVALID_FILE_ATTRIBUTES) &&
            (!(mode & 2) ||
            !(attr & FILE_ATTRIBUTE_READONLY) ||
            (attr & FILE_ATTRIBUTE_DIRECTORY)));
#else

    Py_BEGIN_ALLOW_THREADS
#ifdef HAVE_FACCESSAT
    if ((dir_fd != DEFAULT_DIR_FD) ||
        effective_ids ||
        !follow_symlinks) {
        int flags = 0;
        if (!follow_symlinks)
            flags |= AT_SYMLINK_NOFOLLOW;
        if (effective_ids)
            flags |= AT_EACCESS;
        result = faccessat(dir_fd, path->narrow, mode, flags);
    }
    else
#endif
        result = access(path->narrow, mode);
    Py_END_ALLOW_THREADS
    return_value = PyBool_FromLong(!result);
#endif

#ifndef HAVE_FACCESSAT
exit:
#endif
    return return_value;
}
