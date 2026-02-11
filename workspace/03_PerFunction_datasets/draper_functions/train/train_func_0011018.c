print_buffer_ts (GstPad * pad, GstBuffer * buffer, gpointer user_data)
{
  GST_DEBUG_OBJECT (pad, "  ts: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)));
  return TRUE;
}
