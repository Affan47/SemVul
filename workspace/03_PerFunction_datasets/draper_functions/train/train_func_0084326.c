translate_outgoing_segment (GnlObject * object, GstEvent * event)
{
  const GstSegment *orig;
  GstSegment segment;
  GstEvent *event2;
  guint32 seqnum = GST_EVENT_SEQNUM (event);


  gst_event_parse_segment (event, &orig);

  GST_DEBUG_OBJECT (object,
      "Got SEGMENT %" GST_TIME_FORMAT " -- %" GST_TIME_FORMAT " // %"
      GST_TIME_FORMAT, GST_TIME_ARGS (orig->start), GST_TIME_ARGS (orig->stop),
      GST_TIME_ARGS (orig->time));

  if (G_UNLIKELY (orig->format != GST_FORMAT_TIME)) {
    GST_WARNING_OBJECT (object,
        "Can't translate segments with format != GST_FORMAT_TIME");
    return event;
  }

  gst_segment_copy_into (orig, &segment);

  gnl_media_to_object_time (object, orig->time, &segment.time);

  if (G_UNLIKELY (segment.time > G_MAXINT64))
    GST_WARNING_OBJECT (object, "Return value too big...");

  GST_DEBUG_OBJECT (object,
      "Sending SEGMENT %" GST_TIME_FORMAT " -- %" GST_TIME_FORMAT " // %"
      GST_TIME_FORMAT, GST_TIME_ARGS (segment.start),
      GST_TIME_ARGS (segment.stop), GST_TIME_ARGS (segment.time));

  event2 = gst_event_new_segment (&segment);
  GST_EVENT_SEQNUM (event2) = seqnum;
  gst_event_unref (event);

  return event2;
}
