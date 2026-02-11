gst_ssa_parse_setcaps (GstPad * sinkpad, GstCaps * caps)
{
  GstSsaParse *parse = GST_SSA_PARSE (GST_PAD_PARENT (sinkpad));
  const GValue *val;
  GstStructure *s;
  const guchar bom_utf8[] = { 0xEF, 0xBB, 0xBF };
  GstBuffer *priv;
  gchar *data;
  guint size;

  s = gst_caps_get_structure (caps, 0);
  val = gst_structure_get_value (s, "codec_data");
  if (val == NULL) {
    parse->framed = FALSE;
    GST_ERROR ("Only SSA subtitles embedded in containers are supported");
    return FALSE;
  }

  parse->framed = TRUE;
  parse->send_tags = TRUE;

  priv = (GstBuffer *) gst_value_get_mini_object (val);
  g_return_val_if_fail (priv != NULL, FALSE);

  gst_buffer_ref (priv);

  data = (gchar *) GST_BUFFER_DATA (priv);
  size = GST_BUFFER_SIZE (priv);

  if (size >= 3 && memcmp (data, bom_utf8, 3) == 0) {
    data += 3;
    size -= 3;
  }

  if (!strstr (data, "[Script Info]")) {
    GST_WARNING_OBJECT (parse, "Invalid Init section - no Script Info header");
    gst_buffer_unref (priv);
    return FALSE;
  }

  if (!g_utf8_validate (data, size, NULL)) {
    GST_WARNING_OBJECT (parse, "Init section is not valid UTF-8");
    gst_buffer_unref (priv);
    return FALSE;
  }


  parse->ini = g_strndup (data, size);
  GST_LOG_OBJECT (parse, "Init section:\n%s", parse->ini);

  gst_buffer_unref (priv);

  return TRUE;
}
