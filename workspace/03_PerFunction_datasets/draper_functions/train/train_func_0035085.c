gst_tcp_socket_read (GstElement * this, int socket, void *buf, size_t count,
    GstPoll * fdset)
{
  ssize_t n;
  size_t bytes_read;
  int num_to_read;
  int ret;

  bytes_read = 0;

  while (bytes_read < count) {


    if ((ret = gst_poll_wait (fdset, GST_CLOCK_TIME_NONE)) <= 0) {
      if (ret == -1 && errno == EBUSY)
        goto cancelled;
      else
        goto select_error;
    }


    if (ioctl (socket, FIONREAD, &num_to_read) < 0)
      goto ioctl_error;

    if (num_to_read == 0)
      goto got_eos;


    num_to_read = MIN (num_to_read, count - bytes_read);

    n = read (socket, ((guint8 *) buf) + bytes_read, num_to_read);

    if (n < 0)
      goto read_error;

    if (n < num_to_read)
      goto short_read;

    bytes_read += num_to_read;
  }

  return GST_FLOW_OK;


select_error:
  {
    GST_ELEMENT_ERROR (this, RESOURCE, READ, (NULL),
        ("select failed: %s", g_strerror (errno)));
    return GST_FLOW_ERROR;
  }
cancelled:
  {
    GST_DEBUG_OBJECT (this, "Select was cancelled");
    return GST_FLOW_WRONG_STATE;
  }
ioctl_error:
  {
    GST_ELEMENT_ERROR (this, RESOURCE, READ, (NULL),
        ("ioctl failed: %s", g_strerror (errno)));
    return GST_FLOW_ERROR;
  }
got_eos:
  {
    GST_DEBUG_OBJECT (this, "Got EOS on socket stream");
    return GST_FLOW_UNEXPECTED;
  }
read_error:
  {
    GST_ELEMENT_ERROR (this, RESOURCE, READ, (NULL),
        ("read failed: %s", g_strerror (errno)));
    return GST_FLOW_ERROR;
  }
short_read:
  {
    GST_ELEMENT_ERROR (this, RESOURCE, READ, (NULL),
        ("short read: wanted %d bytes, got %" G_GSSIZE_FORMAT, num_to_read, n));
    return GST_FLOW_ERROR;
  }
}
