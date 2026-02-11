gst_dccp_server_src_start (GstBaseSrc * bsrc)
{
  GstDCCPServerSrc *src = GST_DCCP_SERVER_SRC (bsrc);

  if (src->client_sock_fd == DCCP_DEFAULT_CLIENT_SOCK_FD) {

    if ((src->sock_fd = gst_dccp_create_new_socket (GST_ELEMENT (src))) < 0) {
      return FALSE;
    }

    if (!gst_dccp_make_address_reusable (GST_ELEMENT (src), src->sock_fd)) {
      return FALSE;
    }


    memset (&src->server_sin, 0, sizeof (src->server_sin));
    src->server_sin.sin_family = AF_INET;
    src->server_sin.sin_port = htons (src->port);
    src->server_sin.sin_addr.s_addr = htonl (INADDR_ANY);


    if (!gst_dccp_bind_server_socket (GST_ELEMENT (src), src->sock_fd,
            src->server_sin)) {
      return FALSE;
    }

    if (!gst_dccp_set_ccid (GST_ELEMENT (src), src->sock_fd, src->ccid)) {
      return FALSE;
    }

    if (!gst_dccp_listen_server_socket (GST_ELEMENT (src), src->sock_fd)) {
      return FALSE;
    }

    src->client_sock_fd = gst_dccp_server_wait_connections (GST_ELEMENT (src),
        src->sock_fd);
    if (src->client_sock_fd == -1) {
      return FALSE;
    }


    g_signal_emit (src, gst_dccp_server_src_signals[SIGNAL_CONNECTED], 0,
        src->client_sock_fd);
  }

  return TRUE;
}
