_GetProgramCmdline(char *buf, int size)
  {
    int fd = jalib::open("/proc/self/cmdline", O_RDONLY, 0);
    int rc;
    JASSERT(fd >= 0);

    rc = jalib::readAll(fd, buf, size);
    jalib::close(fd);
    return rc;
  }
