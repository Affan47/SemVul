gst_avi_demux_parse_idit (GstAviDemux * avi, GstBuffer * buf)
{
  gchar *data = (gchar *) GST_BUFFER_DATA (buf);
  guint size = GST_BUFFER_SIZE (buf);
  gchar *safedata = NULL;


  while (size > 0 && g_ascii_isspace (data[0])) {
    data++;
    size--;
  }

  if (size == 0) {
    goto non_parsable;
  }


  safedata = g_strndup (data, size);


  if (g_ascii_isdigit (data[0])) {
    gst_avi_demux_parse_idit_nums_only (avi, safedata);
    g_free (safedata);
    return;
  } else if (g_ascii_isalpha (data[0])) {
    gst_avi_demux_parse_idit_text (avi, safedata);
    g_free (safedata);
    return;
  }

  g_free (safedata);

non_parsable:
  GST_WARNING_OBJECT (avi, "IDIT tag has no parsable info");
}
