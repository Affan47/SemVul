gst_h263_parse_sink_event (GstBaseParse * parse, GstEvent * event)
{
  GstH263Parse *h263parse;

  h263parse = GST_H263_PARSE (parse);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_TAG:
    {
      GstTagList *taglist;

      gst_event_parse_tag (event, &taglist);

      if (gst_tag_list_get_uint (taglist, GST_TAG_BITRATE, &h263parse->bitrate))
        GST_DEBUG_OBJECT (h263parse, "got bitrate tag: %u", h263parse->bitrate);

      break;
    }
    default:
      break;
  }

  return GST_BASE_PARSE_CLASS (parent_class)->sink_event (parse, event);
}
