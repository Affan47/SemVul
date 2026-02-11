gst_fd_sink_event (GstBaseSink * sink, GstEvent * event)
{
  GstEventType type;
  GstFdSink *fdsink;

  fdsink = GST_FD_SINK (sink);

  type = GST_EVENT_TYPE (event);

  switch (type) {
    case GST_EVENT_SEGMENT:
    {
      const GstSegment *segment;

      gst_event_parse_segment (event, &segment);

      if (segment->format == GST_FORMAT_BYTES) {


        if (fdsink->current_pos != segment->start) {


          if (!gst_fd_sink_do_seek (fdsink, (guint64) segment->start))
            goto seek_failed;
        }
      } else {
        GST_DEBUG_OBJECT (fdsink,
            "Ignored SEGMENT event of format %u (%s)", (guint) segment->format,
            gst_format_get_name (segment->format));
      }
      break;
    }
    default:
      break;
  }

  return GST_BASE_SINK_CLASS (parent_class)->event (sink, event);

seek_failed:
  {
    GST_ELEMENT_ERROR (fdsink, RESOURCE, SEEK, (NULL),
        ("Error while seeking on file descriptor %d: %s",
            fdsink->fd, g_strerror (errno)));
    gst_event_unref (event);
    return FALSE;
  }

}
