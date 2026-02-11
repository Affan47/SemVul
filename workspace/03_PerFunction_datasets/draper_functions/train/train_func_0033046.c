gst_dvswitch_uri_update (GstDvswitchUri * uri, const gchar * host, gint port)
{
  if (host) {
    g_free (uri->host);
    uri->host = g_strdup (host);
    if (strchr (host, ':'))
      uri->is_ipv6 = TRUE;
    else
      uri->is_ipv6 = FALSE;
  }
  if (port != -1)
    uri->port = port;

  return 0;
}
