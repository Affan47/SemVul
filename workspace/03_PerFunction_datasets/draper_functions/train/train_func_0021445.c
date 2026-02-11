updwtmpx(const char *wtmpx_file, const struct utmpx *ut) {
  int fd = open(wtmpx_file, O_WRONLY|O_APPEND);
  if (fd<0) return;
  fcntl (fd, F_SETFD, FD_CLOEXEC);
  write(fd, ut, sizeof(struct utmpx));
  close(fd);
}
