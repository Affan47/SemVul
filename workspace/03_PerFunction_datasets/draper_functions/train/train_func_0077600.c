gst_message_parse_qos_values (GstMessage * message, gint64 * jitter,
    gdouble * proportion, gint * quality)
{
  GstStructure *structure;

  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_QOS);

  structure = GST_MESSAGE_STRUCTURE (message);
  gst_structure_id_get (structure,
      GST_QUARK (JITTER), G_TYPE_INT64, jitter,
      GST_QUARK (PROPORTION), G_TYPE_DOUBLE, proportion,
      GST_QUARK (QUALITY), G_TYPE_INT, quality, NULL);
}
