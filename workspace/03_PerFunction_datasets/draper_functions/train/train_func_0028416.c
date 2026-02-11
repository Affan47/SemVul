gst_uri_handler_set_uri (GstURIHandler * handler, const gchar * uri)
{
  GstURIHandlerInterface *iface;
  gboolean ret;
  gchar *new_uri, *protocol, *location, *colon;

  g_return_val_if_fail (GST_IS_URI_HANDLER (handler), FALSE);
  g_return_val_if_fail (gst_uri_is_valid (uri), FALSE);

  iface = GST_URI_HANDLER_GET_INTERFACE (handler);
  g_return_val_if_fail (iface != NULL, FALSE);
  g_return_val_if_fail (iface->set_uri != NULL, FALSE);

  protocol = gst_uri_get_protocol (uri);

  colon = strstr (uri, ":");
  location = g_strdup (colon);

  new_uri = g_strdup_printf ("%s%s", protocol, location);

  ret = iface->set_uri (handler, uri);

  g_free (new_uri);
  g_free (location);
  g_free (protocol);

  return ret;
}
