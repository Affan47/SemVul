gst_gdp_depay_src_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstGDPDepay *this;
  gboolean res = TRUE;

  this = GST_GDP_DEPAY (parent);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:

      gst_event_unref (event);
      res = FALSE;
      break;
    case GST_EVENT_QOS:
    case GST_EVENT_NAVIGATION:
    default:

      res = gst_pad_push_event (this->sinkpad, event);
      break;
  }

  return res;
}
