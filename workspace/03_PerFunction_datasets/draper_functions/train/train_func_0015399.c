gst_curl_smtp_sink_set_mime_type (GstCurlBaseSink * bcsink, GstCaps * caps)
{
  GstCurlSmtpSink *sink = GST_CURL_SMTP_SINK (bcsink);
  GstStructure *structure;
  const gchar *mime_type;

  if (sink->content_type != NULL) {
    return;
  }

  structure = gst_caps_get_structure (caps, 0);
  mime_type = gst_structure_get_name (structure);
  sink->content_type = g_strdup (mime_type);
}
