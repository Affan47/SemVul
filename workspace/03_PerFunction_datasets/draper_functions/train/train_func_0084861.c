kvu_fd_write(int fd, const void *buf, size_t count, int timeout)
{
  int nfds = 1;
  struct pollfd ufds;
  ssize_t rescount = 0;

  ufds.fd = fd;
  ufds.events = POLLOUT;
  ufds.revents = 0;

  int ret = poll(&ufds, nfds, timeout);
  if (ret > 0) {
    if (ufds.revents & POLLOUT) {
      rescount = ::write(fd, buf, count);
    }
  }
  else if (ret == 0) {

    rescount = -1;
  }
  return(rescount);
}
