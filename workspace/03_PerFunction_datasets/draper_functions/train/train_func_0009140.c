close_local_endpoint(struct connection *conn) {
  struct mg_connection *c = &conn->mg_conn;

  int keep_alive = should_keep_alive(&conn->mg_conn) &&
    (conn->endpoint_type == EP_FILE || conn->endpoint_type == EP_USER);
  DBG(("%p %d %d %d", conn, conn->endpoint_type, keep_alive,
       conn->ns_conn->flags));

  switch (conn->endpoint_type) {
    case EP_PUT:
    case EP_FILE:
      close(conn->endpoint.fd);
      break;
    case EP_CGI:
      if (conn->endpoint.cgi_conn != NULL) {
        conn->endpoint.cgi_conn->flags |= NSF_CLOSE_IMMEDIATELY;
        conn->endpoint.cgi_conn->connection_data = NULL;
      }
      break;
    default: break;
  }

#ifndef MONGOOSE_NO_LOGGING
  if (c->status_code > 0 && conn->endpoint_type != EP_CLIENT &&
      c->status_code != 400) {
    log_access(conn, conn->server->config_options[ACCESS_LOG_FILE]);
  }
#endif


  iobuf_remove(&conn->ns_conn->recv_iobuf, conn->mg_conn.content_len);
  conn->endpoint_type = EP_NONE;
  conn->cl = conn->num_bytes_sent = conn->request_len = 0;
  conn->ns_conn->flags &= ~(NSF_FINISHED_SENDING_DATA |
                            NSF_BUFFER_BUT_DONT_SEND | NSF_CLOSE_IMMEDIATELY |
                            MG_HEADERS_SENT | MG_LONG_RUNNING);
  c->request_method = c->uri = c->http_version = c->query_string = NULL;
  c->num_headers = c->status_code = c->is_websocket = c->content_len = 0;
  free(conn->request); conn->request = NULL;
  free(conn->path_info); conn->path_info = NULL;

  if (keep_alive) {
    process_request(conn);
  } else {
    conn->ns_conn->flags |= conn->ns_conn->send_iobuf.len == 0 ?
      NSF_CLOSE_IMMEDIATELY : NSF_FINISHED_SENDING_DATA;
  }
}
