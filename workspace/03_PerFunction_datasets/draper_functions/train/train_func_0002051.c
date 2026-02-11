net_linux_send(JsNetwork *net, int sckt, const void *buf, size_t len) {
  NOT_USED(net);
  fd_set writefds;
  FD_ZERO(&writefds);
  FD_SET(sckt, &writefds);
  struct timeval time;
  time.tv_sec = 0;
  time.tv_usec = 0;
  int n = select(sckt+1, 0, &writefds, 0, &time);
  if (n==SOCKET_ERROR ) {

    return -1;
  } else if (FD_ISSET(sckt, &writefds)) {
    int flags = 0;
#if !defined(SO_NOSIGPIPE) && defined(MSG_NOSIGNAL)
    flags |= MSG_NOSIGNAL;
#endif
    n = (int)send(sckt, buf, len, flags);
    return n;
  } else
    return 0;
}
