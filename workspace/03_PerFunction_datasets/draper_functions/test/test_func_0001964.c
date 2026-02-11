gst_message_parse_progress (GstMessage * message, GstProgressType * type,
    gchar ** code, gchar ** text)
{
  GstStructure *structure;

  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_PROGRESS);

  structure = GST_MESSAGE_STRUCTURE (message);
  gst_structure_id_get (structure,
      GST_QUARK (TYPE), GST_TYPE_PROGRESS_TYPE, type,
      GST_QUARK (CODE), G_TYPE_STRING, code,
      GST_QUARK (TEXT), G_TYPE_STRING, text, NULL);
}
