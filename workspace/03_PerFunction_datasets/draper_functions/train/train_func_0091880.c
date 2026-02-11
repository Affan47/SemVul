uv_guess_handle(uv_file file) {
  struct stat s;

  if (file < 0) {
    uv__set_sys_error(NULL, EINVAL);
    return -1;
  }

  if (isatty(file)) {
    return UV_TTY;
  }

  if (fstat(file, &s)) {
    uv__set_sys_error(NULL, errno);
    return -1;
  }

  if (!S_ISSOCK(s.st_mode) && !S_ISFIFO(s.st_mode)) {
    return UV_FILE;
  }

  return UV_NAMED_PIPE;
}
