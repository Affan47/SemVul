gst_uri_protocol_is_valid (const gchar * protocol)
{
  gchar *endptr;

  g_return_val_if_fail (protocol != NULL, FALSE);

  gst_uri_protocol_check_internal (protocol, &endptr);

  return *endptr == '\0' && endptr != protocol;
}
