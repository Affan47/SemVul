find_bad_fd(int fd, fd_set *set)
{
  struct stat s;
  if (fd >= 0 && fd < FD_SETSIZE && fstat(fd, &s) == -1 && errno == EBADF)
    FD_SET(fd, set);
}
