gst_message_parse_segment_start (GstMessage * message, GstFormat * format,
    gint64 * position)
{
  GstStructure *structure;

  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_SEGMENT_START);

  structure = GST_MESSAGE_STRUCTURE (message);
  if (format)
    *format = (GstFormat)
        g_value_get_enum (gst_structure_id_get_value (structure,
            GST_QUARK (FORMAT)));
  if (position)
    *position =
        g_value_get_int64 (gst_structure_id_get_value (structure,
            GST_QUARK (POSITION)));
}
