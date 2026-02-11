gst_cmml_enc_chain (GstPad * pad, GstBuffer * buffer)
{
  GError *err = NULL;
  GstCmmlEnc *enc = GST_CMML_ENC (GST_PAD_PARENT (pad));


  enc->flow_return = GST_FLOW_OK;

  if (!gst_cmml_parser_parse_chunk (enc->parser,
          (gchar *) GST_BUFFER_DATA (buffer), GST_BUFFER_SIZE (buffer), &err)) {
    GST_ELEMENT_ERROR (enc, STREAM, ENCODE, (NULL), ("%s", err->message));
    g_error_free (err);
    enc->flow_return = GST_FLOW_ERROR;
  }

  gst_buffer_unref (buffer);
  return enc->flow_return;
}
