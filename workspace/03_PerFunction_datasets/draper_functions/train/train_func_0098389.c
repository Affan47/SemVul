gst_dccp_client_src_start (GstBaseSrc * bsrc)
{
  GstDCCPClientSrc *src = GST_DCCP_CLIENT_SRC (bsrc);

  if (src->sock_fd == DCCP_DEFAULT_SOCK_FD) {
    gchar *ip = NULL;


    if (!(ip = gst_dccp_host_to_ip (GST_ELEMENT (src), src->host))) {
      GST_ERROR_OBJECT (src, "cannot resolve hostname");
      gst_dccp_client_src_stop (GST_BASE_SRC (src));
      return FALSE;
    }


    memset (&src->server_sin, 0, sizeof (src->server_sin));
    src->server_sin.sin_family = AF_INET;
    src->server_sin.sin_port = htons (src->port);
    src->server_sin.sin_addr.s_addr = inet_addr (ip);
    g_free (ip);


    if ((src->sock_fd = gst_dccp_create_new_socket (GST_ELEMENT (src))) < 0) {
      return FALSE;
    }

    if (!gst_dccp_set_ccid (GST_ELEMENT (src), src->sock_fd, src->ccid)) {
      gst_dccp_client_src_stop (GST_BASE_SRC (src));
      return FALSE;
    }

    if (!gst_dccp_connect_to_server (GST_ELEMENT (src), src->server_sin,
            src->sock_fd)) {
      gst_dccp_client_src_stop (GST_BASE_SRC (src));
      return FALSE;
    }


    g_signal_emit (src, gst_dccp_client_src_signals[SIGNAL_CONNECTED], 0,
        src->sock_fd);
  }

  return TRUE;
}
