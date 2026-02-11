rm_conn_sock(int sock, fd_set *fds, struct proxied_connection *conns) {
  struct proxied_connection *conn;

  if(!(conn = get_conn(sock, conns))) {
    return NULL;
  }

  return rm_conn(conn, fds);
}
