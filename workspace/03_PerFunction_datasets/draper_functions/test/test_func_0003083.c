gst_dccp_server_sink_start (GstBaseSink * bsink)
{
  GstDCCPServerSink *sink = GST_DCCP_SERVER_SINK (bsink);
  Client *client;

  if ((sink->sock_fd = gst_dccp_create_new_socket (GST_ELEMENT (sink))) < 0) {
    return FALSE;
  }

  if (!gst_dccp_make_address_reusable (GST_ELEMENT (sink), sink->sock_fd)) {
    return FALSE;
  }


  memset (&sink->server_sin, 0, sizeof (sink->server_sin));
  sink->server_sin.sin_family = AF_INET;
  sink->server_sin.sin_port = htons (sink->port);
  sink->server_sin.sin_addr.s_addr = htonl (INADDR_ANY);

  if (!gst_dccp_bind_server_socket (GST_ELEMENT (sink), sink->sock_fd,
          sink->server_sin)) {
    return FALSE;
  }

  if (!gst_dccp_set_ccid (GST_ELEMENT (sink), sink->sock_fd, sink->ccid)) {
    return FALSE;
  }

  if (!gst_dccp_listen_server_socket (GST_ELEMENT (sink), sink->sock_fd)) {
    return FALSE;
  }


  if (sink->client_sock_fd == DCCP_DEFAULT_CLIENT_SOCK_FD) {
    sink->client_sock_fd =
        gst_dccp_server_wait_connections (GST_ELEMENT (sink), sink->sock_fd);
  }

  if (sink->client_sock_fd == -1) {
    return FALSE;
  }

  client =
      gst_dccp_server_create_client (GST_ELEMENT (sink), sink->client_sock_fd);
  sink->clients = g_list_append (sink->clients, client);

  pthread_mutex_init (&lock, NULL);

  if (sink->wait_connections == TRUE) {
    pthread_create (&accept_thread_id, NULL, gst_dccp_server_accept_new_clients,
        sink);
    pthread_detach (accept_thread_id);
  }

  return TRUE;
}
