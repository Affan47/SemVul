check_error(int ret, int io, int fd)
{
  if (ret > 0)
    return ret;
  if (ret == 0)
  {
    send_error("%s failed on %s: EOF", IO_TYPE(io), FD_NAME(fd));
    exit(1);
  }


  switch (errno)
  {
    case EINPROGRESS:
    case EWOULDBLOCK:
#if EAGAIN != EWOULDBLOCK
    case EAGAIN:
#endif
    case EALREADY:
    case EINTR:
#ifdef ERESTART
    case ERESTART:
#endif

      return 0;
  }


  send_error("%s failed on %s: %s",
             IO_TYPE(io),
             FD_NAME(fd),
             strerror(errno));
  exit(1);
}
