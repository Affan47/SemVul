tor_accept_socket(tor_socket_t sockfd, struct sockaddr *addr, socklen_t *len)
{
  tor_socket_t s;
#if defined(HAVE_ACCEPT4) && defined(SOCK_CLOEXEC)
#define LINUX_CLOEXEC_ACCEPT
  s = accept4(sockfd, addr, len, SOCK_CLOEXEC);
#else
  s = accept(sockfd, addr, len);
#endif
  if (SOCKET_OK(s)) {
#if !defined(LINUX_CLOEXEC_ACCEPT) && defined(FD_CLOEXEC)
    fcntl(s, F_SETFD, FD_CLOEXEC);
#endif
    socket_accounting_lock();
    ++n_sockets_open;
    mark_socket_open(s);
    socket_accounting_unlock();
  }
  return s;
}
