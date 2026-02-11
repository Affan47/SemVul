ns_write_to_socket(struct ns_connection *conn) {
  struct iobuf *io = &conn->send_iobuf;
  int n = 0;

#ifdef NS_ENABLE_SSL
  if (conn->ssl != NULL) {
    n = SSL_write(conn->ssl, io->buf, io->len);
    if (n < 0) {
      int ssl_err = SSL_get_error(conn->ssl, n);
      DBG(("%p %d %d", conn, n, ssl_err));
      if (ssl_err == 2 || ssl_err == 3) {
        return;
      } else {
        conn->flags |= NSF_CLOSE_IMMEDIATELY;
      }
    }
  } else
#endif
  { n = send(conn->sock, io->buf, io->len, 0); }

  DBG(("%p -> %d bytes [%.*s%s]", conn, n, io->len < 40 ? io->len : 40,
       io->buf, io->len < 40 ? "" : "..."));

  ns_call(conn, NS_SEND, &n);
  if (ns_is_error(n)) {
    conn->flags |= NSF_CLOSE_IMMEDIATELY;
  } else if (n > 0) {
    iobuf_remove(io, n);
  }

  if (io->len == 0 && conn->flags & NSF_FINISHED_SENDING_DATA) {
    conn->flags |= NSF_CLOSE_IMMEDIATELY;
  }
}
