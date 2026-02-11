gst_message_set_qos_values (GstMessage * message, gint64 jitter,
    gdouble proportion, gint quality)
{
  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_QOS);

  gst_structure_id_set (message->structure,
      GST_QUARK (JITTER), G_TYPE_INT64, jitter,
      GST_QUARK (PROPORTION), G_TYPE_DOUBLE, proportion,
      GST_QUARK (QUALITY), G_TYPE_INT, quality, NULL);
}
