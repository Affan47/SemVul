gst_multi_fd_sink_handle_client_read (GstMultiFdSink * sink,
    GstTCPClient * client)
{
  int avail, fd;
  gboolean ret;
  GstMultiHandleClient *mhclient = (GstMultiHandleClient *) client;

  fd = client->gfd.fd;

  if (ioctl (fd, FIONREAD, &avail) < 0)
    goto ioctl_failed;

  GST_DEBUG_OBJECT (sink, "%s select reports client read of %d bytes",
      mhclient->debug, avail);

  ret = TRUE;

  if (avail == 0) {

    GST_DEBUG_OBJECT (sink, "%s client asked for close, removing",
        mhclient->debug);
    mhclient->status = GST_CLIENT_STATUS_CLOSED;
    ret = FALSE;
  } else if (avail < 0) {
    GST_WARNING_OBJECT (sink, "%s avail < 0, removing", mhclient->debug);
    mhclient->status = GST_CLIENT_STATUS_ERROR;
    ret = FALSE;
  } else {
    guint8 dummy[512];
    gint nread;


    do {

      gint to_read = MIN (avail, 512);

      GST_DEBUG_OBJECT (sink, "%s client wants us to read %d bytes",
          mhclient->debug, to_read);

      nread = read (fd, dummy, to_read);
      if (nread < -1) {
        GST_WARNING_OBJECT (sink, "%s could not read %d bytes: %s (%d)",
            mhclient->debug, to_read, g_strerror (errno), errno);
        mhclient->status = GST_CLIENT_STATUS_ERROR;
        ret = FALSE;
        break;
      } else if (nread == 0) {
        GST_WARNING_OBJECT (sink, "%s 0 bytes in read, removing",
            mhclient->debug);
        mhclient->status = GST_CLIENT_STATUS_ERROR;
        ret = FALSE;
        break;
      }
      avail -= nread;
    }
    while (avail > 0);
  }
  return ret;


ioctl_failed:
  {
    GST_WARNING_OBJECT (sink, "%s ioctl failed: %s (%d)",
        mhclient->debug, g_strerror (errno), errno);
    mhclient->status = GST_CLIENT_STATUS_ERROR;
    return FALSE;
  }
}
