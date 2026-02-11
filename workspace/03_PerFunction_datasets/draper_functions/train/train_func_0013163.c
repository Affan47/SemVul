speed_sink_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstSpeed *filter = GST_SPEED (parent);
  gboolean ret = FALSE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEGMENT:{
      gdouble rate;
      GstFormat format;
      gint64 start_value, stop_value, base;
      const GstSegment *segment;
      GstSegment seg;

      gst_event_parse_segment (event, &segment);

      rate = segment->rate;
      format = segment->format;
      start_value = segment->start;
      stop_value = segment->stop;
      base = segment->base;

      gst_event_unref (event);

      if (format != GST_FORMAT_TIME) {
        GST_WARNING_OBJECT (filter, "newsegment event not in TIME format!");
        break;
      }

      g_assert (filter->speed > 0);

      if (start_value >= 0)
        start_value /= filter->speed;
      if (stop_value >= 0)
        stop_value /= filter->speed;
      base /= filter->speed;


      filter->timestamp = start_value;


      filter->offset = GST_BUFFER_OFFSET_NONE;

      gst_segment_init (&seg, GST_FORMAT_TIME);
      seg.rate = rate;
      seg.start = start_value;
      seg.stop = stop_value;
      seg.time = segment->time;
      ret = gst_pad_push_event (filter->srcpad, gst_event_new_segment (&seg));

      break;
    }
    case GST_EVENT_CAPS:
    {
      GstCaps *caps;

      gst_event_parse_caps (event, &caps);
      ret = speed_setcaps (pad, caps);
      if (!ret) {
        gst_event_unref (event);
        return ret;
      }
    }

    default:
      ret = gst_pad_event_default (pad, parent, event);
      break;
  }
  return ret;
}
