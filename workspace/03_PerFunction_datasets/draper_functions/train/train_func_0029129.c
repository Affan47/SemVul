gst_message_parse_warning (GstMessage * message, GError ** gerror,
    gchar ** debug)
{
  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_WARNING);

  gst_structure_id_get (GST_MESSAGE_STRUCTURE (message),
      GST_QUARK (GERROR), G_TYPE_ERROR, gerror,
      GST_QUARK (DEBUG), G_TYPE_STRING, debug, NULL);
}
