uv_tcp_listen(uv_tcp_t* tcp, int backlog, uv_connection_cb cb) {
  static int single_accept = -1;
  int err;

  if (tcp->delayed_error)
    return tcp->delayed_error;

  if (single_accept == -1) {
    const char* val = getenv("UV_TCP_SINGLE_ACCEPT");
    single_accept = (val != NULL && atoi(val) != 0);
  }

  if (single_accept)
    tcp->flags |= UV_TCP_SINGLE_ACCEPT;

  err = maybe_new_socket(tcp, AF_INET, UV_STREAM_READABLE);
  if (err)
    return err;

  if (listen(tcp->io_watcher.fd, backlog))
    return -errno;

  tcp->connection_cb = cb;


  tcp->io_watcher.cb = uv__server_io;
  uv__io_start(tcp->loop, &tcp->io_watcher, UV__POLLIN);

  return 0;
}
