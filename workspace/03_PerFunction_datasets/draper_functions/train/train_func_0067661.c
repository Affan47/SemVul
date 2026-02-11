gst_funnel_sink_event (GstPad * pad, GstEvent * event)
{
  GstFunnel *funnel = GST_FUNNEL (gst_pad_get_parent (pad));
  GstFunnelPad *fpad = GST_FUNNEL_PAD_CAST (pad);
  gboolean forward = TRUE;
  gboolean res = TRUE;

  if (G_UNLIKELY (funnel == NULL)) {
    gst_event_unref (event);
    return FALSE;
  }

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_NEWSEGMENT:
    {
      gboolean update;
      gdouble rate, arate;
      GstFormat format;
      gint64 start;
      gint64 stop;
      gint64 time;

      gst_event_parse_new_segment_full (event, &update, &rate, &arate,
          &format, &start, &stop, &time);

      GST_OBJECT_LOCK (funnel);
      gst_segment_set_newsegment_full (&fpad->segment, update, rate, arate,
          format, start, stop, time);
      GST_OBJECT_UNLOCK (funnel);

      forward = FALSE;
    }
      break;
    case GST_EVENT_FLUSH_STOP:
    {
      GST_OBJECT_LOCK (funnel);
      gst_segment_init (&fpad->segment, GST_FORMAT_UNDEFINED);
      funnel->has_segment = FALSE;
      GST_OBJECT_UNLOCK (funnel);
    }
      break;
    default:
      break;
  }

  if (forward)
    res = gst_pad_push_event (funnel->srcpad, event);
  else
    gst_event_unref (event);

  gst_object_unref (funnel);

  return res;
}
