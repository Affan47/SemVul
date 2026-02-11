set_encoding_element (GstElement * element, gchar * encoding)
{
  GST_DEBUG_OBJECT (element, "setting encoding to %s", GST_STR_NULL (encoding));
  g_object_set (G_OBJECT (element), "subtitle-encoding", encoding, NULL);
}
