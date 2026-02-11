gst_multiudpsink_set_clients_string (GstMultiUDPSink * sink,
    const gchar * string)
{
  gchar **clients;
  gint i;

  clients = g_strsplit (string, ",", 0);

  g_mutex_lock (&sink->client_lock);

  gst_multiudpsink_clear_internal (sink, FALSE);
  for (i = 0; clients[i]; i++) {
    gchar *host, *p;
    gint64 port = 0;

    host = clients[i];
    p = strstr (clients[i], ":");
    if (p != NULL) {
      *p = '\0';
      port = g_ascii_strtoll (p + 1, NULL, 10);
    }
    if (port != 0)
      gst_multiudpsink_add_internal (sink, host, port, FALSE);
  }
  g_mutex_unlock (&sink->client_lock);

  g_strfreev (clients);
}
