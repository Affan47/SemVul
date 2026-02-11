gst_siren_dec_parse (GstAudioDecoder * dec, GstAdapter * adapter,
    gint * offset, gint * length)
{
  gint size;
  GstFlowReturn ret;

  size = gst_adapter_available (adapter);
  g_return_val_if_fail (size > 0, GST_FLOW_ERROR);


  if (size > 40) {
    ret = GST_FLOW_OK;
    *offset = 0;
    *length = size - (size % 40);
  } else {
    ret = GST_FLOW_EOS;
  }

  return ret;
}
