uv__tcp_keepalive(int fd, int on, unsigned int delay) {
  if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(on)))
    return -errno;

#ifdef TCP_KEEPIDLE
  if (on && setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &delay, sizeof(delay)))
    return -errno;
#endif


#if defined(TCP_KEEPALIVE) && !defined(__sun)
  if (on && setsockopt(fd, IPPROTO_TCP, TCP_KEEPALIVE, &delay, sizeof(delay)))
    return -errno;
#endif

  return 0;
}
