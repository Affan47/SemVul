writeAll ( const char* buf, size_t len )
{
  int origLen = len;
  while (len > 0) {
    fd_set wfds;
    struct timeval tv;
    int retval;

    int tmp_sockfd = _sockfd;
    if (tmp_sockfd == -1) {
      return -1;
    }


    FD_ZERO(&wfds);
    FD_SET(tmp_sockfd, &wfds);


    tv.tv_sec = 30;
    tv.tv_usec = 0;

    retval = jalib::select(tmp_sockfd+1, NULL, &wfds, NULL, &tv);


    if (retval == -1) {
      if (errno == EBADF || errno == EPIPE) {
        JTRACE("Socket already closed");
        return -1;
      }
      JWARNING(retval >= 0) (tmp_sockfd) (JASSERT_ERRNO)
        .Text ("select() failed");
      return -1;
    } else if (retval) {
      errno = 0;
      ssize_t cnt = write(buf, len);
      if (cnt < 0 && (errno == EBADF || errno == EPIPE)) {
        JTRACE("Remote peer disconnected, write failed");
        return -1;
      } else if (cnt <= 0 && errno != EAGAIN && errno != EINTR) {
        JWARNING(cnt > 0) (cnt) (len) (JASSERT_ERRNO)
          .Text("JSocket write failure");
        return -1;
      }
      if (cnt > 0) {
        buf += cnt;
        len -= cnt;
      }
    } else {
      JTRACE("still waiting for data") (tmp_sockfd) (len);
    }
  }
  return origLen;
}
