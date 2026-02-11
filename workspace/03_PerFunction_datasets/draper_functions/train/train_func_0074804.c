gst_base_parse_src_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstBaseParse *parse;
  GstBaseParseClass *bclass;
  gboolean ret = TRUE;

  parse = GST_BASE_PARSE (parent);
  bclass = GST_BASE_PARSE_GET_CLASS (parse);

  GST_DEBUG_OBJECT (parse, "event %d, %s", GST_EVENT_TYPE (event),
      GST_EVENT_TYPE_NAME (event));

  if (bclass->src_event)
    ret = bclass->src_event (parse, event);
  else
    gst_event_unref (event);

  return ret;
}
