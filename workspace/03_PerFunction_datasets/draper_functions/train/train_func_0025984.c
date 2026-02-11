gst_event_copy_segment (GstEvent * event, GstSegment * segment)
{
  const GstSegment *src;

  g_return_if_fail (GST_IS_EVENT (event));
  g_return_if_fail (GST_EVENT_TYPE (event) == GST_EVENT_SEGMENT);

  if (segment) {
    gst_event_parse_segment (event, &src);
    gst_segment_copy_into (src, segment);
  }
}
