gst_pb_utils_get_sink_description (const gchar * protocol)
{
  gchar *proto_uc, *ret;

  g_return_val_if_fail (protocol != NULL, NULL);


  proto_uc = g_ascii_strup (protocol, -1);


  ret = g_strdup_printf ("%s protocol sink", proto_uc);

  g_free (proto_uc);

  return ret;
}
