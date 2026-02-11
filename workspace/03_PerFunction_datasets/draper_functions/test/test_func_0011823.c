gst_ssa_parse_push_line (GstSsaParse * parse, gchar * txt,
    GstClockTime start, GstClockTime duration)
{
  GstFlowReturn ret;
  GstBuffer *buf;
  gchar *t, *escaped;
  gint num, i, len;

  num = atoi (txt);
  GST_LOG_OBJECT (parse, "Parsing line #%d at %" GST_TIME_FORMAT,
      num, GST_TIME_ARGS (start));


  t = txt;
  for (i = 0; i < 8; ++i) {
    t = strchr (t, ',');
    if (t == NULL)
      return GST_FLOW_ERROR;
    ++t;
  }

  GST_LOG_OBJECT (parse, "Text : %s", t);

  if (gst_ssa_parse_remove_override_codes (parse, t)) {
    GST_LOG_OBJECT (parse, "Clean: %s", t);
  }


  escaped = g_markup_printf_escaped ("%s", t);

  len = strlen (escaped);


  buf = gst_buffer_new_and_alloc (len + 1);
  gst_buffer_fill (buf, 0, escaped, len + 1);
  gst_buffer_set_size (buf, len);
  g_free (escaped);

  GST_BUFFER_TIMESTAMP (buf) = start;
  GST_BUFFER_DURATION (buf) = duration;

  GST_LOG_OBJECT (parse, "Pushing buffer with timestamp %" GST_TIME_FORMAT
      " and duration %" GST_TIME_FORMAT, GST_TIME_ARGS (start),
      GST_TIME_ARGS (duration));

  ret = gst_pad_push (parse->srcpad, buf);

  if (ret != GST_FLOW_OK) {
    GST_DEBUG_OBJECT (parse, "Push of text '%s' returned flow %s", txt,
        gst_flow_get_name (ret));
  }

  return ret;
}
