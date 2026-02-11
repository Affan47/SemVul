uv_udp_open(uv_udp_t* handle, uv_os_sock_t sock) {
  int yes;


  if (handle->io_watcher.fd != -1)
    return -EALREADY;

  yes = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes))
    return -errno;


#ifdef SO_REUSEPORT
  yes = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof yes))
    return -errno;
#endif

  handle->io_watcher.fd = sock;
  return 0;
}
