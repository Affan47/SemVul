gst_message_parse_buffering (GstMessage * message, gint * percent)
{
  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_BUFFERING);

  if (percent)
    *percent = g_value_get_int (gst_structure_id_get_value (message->structure,
            GST_QUARK (BUFFER_PERCENT)));
}
