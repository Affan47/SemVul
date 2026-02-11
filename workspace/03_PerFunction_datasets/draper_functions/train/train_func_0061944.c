gst_cmml_dec_new_buffer (GstCmmlDec * dec,
    guchar * data, gint size, GstBuffer ** buffer)
{
  GstFlowReturn res;

  res = gst_pad_alloc_buffer (dec->srcpad, GST_BUFFER_OFFSET_NONE,
      size, gst_static_pad_template_get_caps (&gst_cmml_dec_src_factory),
      buffer);

  if (res == GST_FLOW_OK) {
    if (data)
      memcpy (GST_BUFFER_DATA (*buffer), data, size);
    GST_BUFFER_TIMESTAMP (*buffer) = dec->timestamp;
  } else if (res == GST_FLOW_NOT_LINKED) {
    GST_DEBUG_OBJECT (dec, "alloc function return NOT-LINKED, ignoring");
  } else {
    GST_WARNING_OBJECT (dec, "alloc function returned error %s",
        gst_flow_get_name (res));
  }

  return res;
}
