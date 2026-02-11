gst_cmml_enc_parse_preamble (GstCmmlEnc * enc,
    guchar * preamble, guchar * processing_instruction)
{
  GST_INFO_OBJECT (enc, "parsing preamble");


  enc->preamble = (guchar *) g_strconcat ((gchar *) preamble,
      (gchar *) processing_instruction, NULL);
}
