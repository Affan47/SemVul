ps_write_fd(long fd_as_long, char *buffer, long max, psbool *pending, long *status)
{
  int sent;
  int fd = (int)fd_as_long;
  void *buf = (void *)buffer;

  *pending = PSFALSE;
  *status = NO_ERRORS;

  sent = write(fd, buf, max);
  if (sent > 0)
    {}
  else if (errno == EINTR || errno == EAGAIN) {
    if (s48_add_pending_fd(fd, PSFALSE))
      *pending = PSTRUE;
    else
      *status = ENOMEM;
    sent = 0; }
  else {
    *status = errno;
    sent = 0; }

  return sent;
}
