tor_open_socket(int domain, int type, int protocol)
{
  tor_socket_t s;
#ifdef SOCK_CLOEXEC
#define LINUX_CLOEXEC_OPEN_SOCKET
  type |= SOCK_CLOEXEC;
#endif
  s = socket(domain, type, protocol);
  if (SOCKET_OK(s)) {
#if !defined(LINUX_CLOEXEC_OPEN_SOCKET) && defined(FD_CLOEXEC)
    fcntl(s, F_SETFD, FD_CLOEXEC);
#endif
    socket_accounting_lock();
    ++n_sockets_open;
    mark_socket_open(s);
    socket_accounting_unlock();
  }
  return s;
}
