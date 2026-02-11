ns_add_sock(struct ns_server *s, sock_t sock, void *p) {
  struct ns_connection *conn;
  if ((conn = (struct ns_connection *) NS_MALLOC(sizeof(*conn))) != NULL) {
    memset(conn, 0, sizeof(*conn));
    ns_set_non_blocking_mode(sock);
    conn->sock = sock;
    conn->connection_data = p;
    conn->server = s;
    conn->last_io_time = time(NULL);
    ns_add_conn(s, conn);
    DBG(("%p %d", conn, sock));
  }
  return conn;
}
