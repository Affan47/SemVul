terminate_headers(struct mg_connection *c) {
  struct connection *conn = MG_CONN_2_CONN(c);
  if (!(conn->ns_conn->flags & MG_HEADERS_SENT)) {
    mg_send_header(c, "Transfer-Encoding", "chunked");
    mg_write(c, "\r\n", 2);
    conn->ns_conn->flags |= MG_HEADERS_SENT;
  }
}
