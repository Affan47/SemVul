dvdlpcmdec_sink_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstDvdLpcmDec *dvdlpcmdec;
  gboolean res;

  dvdlpcmdec = GST_DVDLPCMDEC (parent);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CAPS:
    {
      GstCaps *caps;

      gst_event_parse_caps (event, &caps);
      res = gst_dvdlpcmdec_setcaps (pad, caps);
      gst_event_unref (event);
      break;
    }
    case GST_EVENT_SEGMENT:
    {
      GstSegment seg;

      gst_event_copy_segment (event, &seg);

      GST_DEBUG_OBJECT (dvdlpcmdec, "segment %" GST_SEGMENT_FORMAT, &seg);

      dvdlpcmdec->segment = seg;

      if (seg.format == GST_FORMAT_TIME) {
        dvdlpcmdec->timestamp = GST_CLOCK_TIME_NONE;
      } else {
        dvdlpcmdec->timestamp = 0;
      }
      res = gst_pad_push_event (dvdlpcmdec->srcpad, event);
      break;
    }
    case GST_EVENT_FLUSH_STOP:
      gst_segment_init (&dvdlpcmdec->segment, GST_FORMAT_UNDEFINED);
      res = gst_pad_push_event (dvdlpcmdec->srcpad, event);
      break;
    default:
      res = gst_pad_push_event (dvdlpcmdec->srcpad, event);
      break;
  }

  return res;
}
