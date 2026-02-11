gst_progress_report_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  GstProgressReport *filter;

  filter = GST_PROGRESS_REPORT (trans);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
    {
      GTimeVal cur_time;

      g_get_current_time (&cur_time);
      gst_progress_report_report (filter, cur_time, NULL);
      break;
    }
    default:
      break;
  }
  return GST_BASE_TRANSFORM_CLASS (parent_class)->sink_event (trans, event);
}
