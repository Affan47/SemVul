gst_video_max_rate_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  GstVideoMaxRate *videomaxrate = GST_VIDEO_MAX_RATE (trans);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_NEWSEGMENT:
    case GST_EVENT_FLUSH_STOP:
      gst_video_max_rate_reset (videomaxrate);
      break;
    default:
      break;
  }

  return TRUE;
}
