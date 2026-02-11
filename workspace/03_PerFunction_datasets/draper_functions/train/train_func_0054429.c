open(const char *pathname, int flags, ...) {
    mode_t mode = 0;

    if (flags & O_CREAT) {
      va_list arg;
      va_start (arg, flags);
      mode = va_arg (arg, int);
      va_end (arg);
    }
    REAL_FUNC_PASSTHROUGH(int, open) (pathname, flags, mode);
  }
