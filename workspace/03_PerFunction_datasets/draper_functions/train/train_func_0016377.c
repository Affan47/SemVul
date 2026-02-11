_Py_open(const char *pathname, int flags)
{
    int fd;
#ifdef MS_WINDOWS
    fd = open(pathname, flags | O_NOINHERIT);
    if (fd < 0)
        return fd;
#else

    int *atomic_flag_works;
#ifdef O_CLOEXEC
    atomic_flag_works = &_Py_open_cloexec_works;
    flags |= O_CLOEXEC;
#else
    atomic_flag_works = NULL;
#endif
    fd = open(pathname, flags);
    if (fd < 0)
        return fd;

    if (set_inheritable(fd, 0, 0, atomic_flag_works) < 0) {
        close(fd);
        return -1;
    }
#endif
    return fd;
}
