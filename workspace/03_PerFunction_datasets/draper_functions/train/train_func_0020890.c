gst_multiudpsink_render (GstBaseSink * bsink, GstBuffer * buffer)
{
  GstMultiUDPSink *sink;
  gint ret, size, num = 0, no_clients = 0;
  guint8 *data;
  GList *clients;
  gint len;

  sink = GST_MULTIUDPSINK (bsink);

  size = GST_BUFFER_SIZE (buffer);
  data = GST_BUFFER_DATA (buffer);

  if (size > UDP_MAX_SIZE) {
    GST_WARNING ("Attempting to send a UDP packet larger than maximum "
        "size (%d > %d)", size, UDP_MAX_SIZE);
  }

  sink->bytes_to_serve += size;


  g_mutex_lock (sink->client_lock);
  GST_LOG_OBJECT (bsink, "about to send %d bytes", size);

  for (clients = sink->clients; clients; clients = g_list_next (clients)) {
    GstUDPClient *client;
    gint count;

    client = (GstUDPClient *) clients->data;
    no_clients++;
    GST_LOG_OBJECT (sink, "sending %d bytes to client %p", size, client);

    count = sink->send_duplicates ? client->refcount : 1;

    while (count--) {
      while (TRUE) {
        len = gst_udp_get_sockaddr_length (&client->theiraddr);

        ret = sendto (*client->sock,
#ifdef G_OS_WIN32
            (char *) data,
#else
            data,
#endif
            size, 0, (struct sockaddr *) &client->theiraddr, len);

        if (ret < 0) {


          if (!socket_error_is_ignorable ()) {
            gchar *errormessage = socket_last_error_message ();
            GST_WARNING_OBJECT (sink, "client %p gave error %d (%s)", client,
                socket_last_error_code (), errormessage);
            g_free (errormessage);
            break;
          }
        } else {
          num++;
          client->bytes_sent += ret;
          client->packets_sent++;
          sink->bytes_served += ret;
          break;
        }
      }
    }
  }
  g_mutex_unlock (sink->client_lock);

  GST_LOG_OBJECT (sink, "sent %d bytes to %d (of %d) clients", size, num,
      no_clients);

  return GST_FLOW_OK;
}
