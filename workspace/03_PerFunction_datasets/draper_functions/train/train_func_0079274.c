gst_mpd_client_add_media_segment (GstActiveStream * stream,
    GstSegmentURLNode * url_node, guint number, guint64 start,
    GstClockTime start_time, GstClockTime duration)
{
  GstMediaSegment *media_segment;

  g_return_val_if_fail (stream->segments != NULL, FALSE);

  media_segment = g_slice_new0 (GstMediaSegment);
  if (media_segment == NULL) {
    GST_WARNING ("Allocation of GstMediaSegment struct failed!");
    return FALSE;
  }

  media_segment->SegmentURL = url_node;
  media_segment->number = number;
  media_segment->start = start;
  media_segment->start_time = start_time;
  media_segment->duration = duration;

  g_ptr_array_add (stream->segments, media_segment);

  return TRUE;
}
