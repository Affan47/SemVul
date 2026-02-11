connection_add_impl(connection_t *conn, int is_connecting)
{
  tor_assert(conn);
  tor_assert(SOCKET_OK(conn->s) ||
             conn->linked ||
             (conn->type == CONN_TYPE_AP &&
              TO_EDGE_CONN(conn)->is_dns_request));

  tor_assert(conn->conn_array_index == -1);
  conn->conn_array_index = smartlist_len(connection_array);
  smartlist_add(connection_array, conn);

#ifdef USE_BUFFEREVENTS
  if (connection_type_uses_bufferevent(conn)) {
    if (SOCKET_OK(conn->s) && !conn->linked) {

#ifdef _WIN32
      if (tor_libevent_using_iocp_bufferevents() &&
          get_options()->UserspaceIOCPBuffers) {
        set_buffer_lengths_to_zero(conn->s);
      }
#endif

      conn->bufev = bufferevent_socket_new(
                         tor_libevent_get_base(),
                         conn->s,
                         BEV_OPT_DEFER_CALLBACKS);
      if (!conn->bufev) {
        log_warn(LD_BUG, "Unable to create socket bufferevent");
        smartlist_del(connection_array, conn->conn_array_index);
        conn->conn_array_index = -1;
        return -1;
      }
      if (is_connecting) {


        bufferevent_socket_connect(conn->bufev, NULL, 0);
      }
      connection_configure_bufferevent_callbacks(conn);
    } else if (conn->linked && conn->linked_conn &&
               connection_type_uses_bufferevent(conn->linked_conn)) {
      tor_assert(!(SOCKET_OK(conn->s)));
      if (!conn->bufev) {
        struct bufferevent *pair[2] = { NULL, NULL };
        if (bufferevent_pair_new(tor_libevent_get_base(),
                                 BEV_OPT_DEFER_CALLBACKS,
                                 pair) < 0) {
          log_warn(LD_BUG, "Unable to create bufferevent pair");
          smartlist_del(connection_array, conn->conn_array_index);
          conn->conn_array_index = -1;
          return -1;
        }
        tor_assert(pair[0]);
        conn->bufev = pair[0];
        conn->linked_conn->bufev = pair[1];
      }
      connection_configure_bufferevent_callbacks(conn);
    } else {
      tor_assert(!conn->linked);
    }

    if (conn->bufev)
      tor_assert(conn->inbuf == NULL);

    if (conn->linked_conn && conn->linked_conn->bufev)
      tor_assert(conn->linked_conn->inbuf == NULL);
  }
#else
  (void) is_connecting;
#endif

  if (!HAS_BUFFEREVENT(conn) && (SOCKET_OK(conn->s) || conn->linked)) {
    conn->read_event = tor_event_new(tor_libevent_get_base(),
         conn->s, EV_READ|EV_PERSIST, conn_read_callback, conn);
    conn->write_event = tor_event_new(tor_libevent_get_base(),
         conn->s, EV_WRITE|EV_PERSIST, conn_write_callback, conn);

  }

  log_debug(LD_NET,"new conn type %s, socket %d, address %s, n_conns %d.",
            conn_type_to_string(conn->type), (int)conn->s, conn->address,
            smartlist_len(connection_array));

  return 0;
}
