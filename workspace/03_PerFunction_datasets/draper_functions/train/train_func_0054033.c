get_inheritable(int fd, int raise)
{
#ifdef MS_WINDOWS
    HANDLE handle;
    DWORD flags;

    if (!_PyVerify_fd(fd)) {
        if (raise)
            PyErr_SetFromErrno(PyExc_OSError);
        return -1;
    }

    handle = (HANDLE)_get_osfhandle(fd);
    if (handle == INVALID_HANDLE_VALUE) {
        if (raise)
            PyErr_SetFromWindowsErr(0);
        return -1;
    }

    if (!GetHandleInformation(handle, &flags)) {
        if (raise)
            PyErr_SetFromWindowsErr(0);
        return -1;
    }

    return (flags & HANDLE_FLAG_INHERIT);
#else
    int flags;

    flags = fcntl(fd, F_GETFD, 0);
    if (flags == -1) {
        if (raise)
            PyErr_SetFromErrno(PyExc_OSError);
        return -1;
    }
    return !(flags & FD_CLOEXEC);
#endif
}
