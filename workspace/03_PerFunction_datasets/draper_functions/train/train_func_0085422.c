_open_fd_noatime (const char *path)
{
  int fd;

#ifdef O_NOATIME
  fd = open_nointr (path, O_RDONLY | O_NOATIME, 0);


  if (fd == -1 && (errno == EPERM || errno == EINVAL))
#endif
    fd = open_nointr (path, O_RDONLY, 0);

  return fd;
}
