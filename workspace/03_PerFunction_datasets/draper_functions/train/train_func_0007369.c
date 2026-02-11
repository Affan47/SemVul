gst_cmml_dec_parse_xml (GstCmmlDec * dec, guchar * data, guint size)
{
  GError *err = NULL;

  if (!gst_cmml_parser_parse_chunk (dec->parser, (gchar *) data, size, &err)) {
    GST_ELEMENT_ERROR (dec, STREAM, DECODE, (NULL), ("%s", err->message));
    g_error_free (err);
    dec->flow_return = GST_FLOW_ERROR;
  }
}
