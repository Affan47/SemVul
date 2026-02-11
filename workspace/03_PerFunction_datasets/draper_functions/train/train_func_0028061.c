gst_dvd_sub_parse_event (GstPad * pad, GstEvent * event)
{
  GstDvdSubParse *parse;
  gboolean ret;

  parse = GST_DVD_SUB_PARSE (gst_pad_get_parent (pad));

  switch GST_EVENT_TYPE
    (event) {
    case GST_EVENT_FLUSH_STOP:
      gst_dvd_sub_parse_reset (parse);

    default:
      ret = gst_pad_event_default (pad, event);
      break;
    }

  gst_object_unref (parse);
  return ret;
}
