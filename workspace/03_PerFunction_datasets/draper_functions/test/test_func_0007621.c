gst_ogg_pad_event (GstPad * pad, GstEvent * event)
{
  gboolean res;
  GstOggDemux *ogg;

  ogg = GST_OGG_DEMUX (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:

      res = gst_ogg_demux_perform_seek (ogg, event);
      gst_event_unref (event);
      break;
    default:
      res = gst_pad_event_default (pad, event);
      break;
  }
  gst_object_unref (ogg);

  return res;
}
