SetCloseOnExec(int fd) {
  int flags = fcntl(fd, F_GETFD, 0);
  int r = fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
  if (r != 0) {
    perror("SetCloseOnExec()");
  }
  return r;
}
