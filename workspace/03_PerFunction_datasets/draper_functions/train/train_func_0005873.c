gst_auto_convert_sink_buffer_alloc (GstPad * pad, guint64 offset,
    guint size, GstCaps * caps, GstBuffer ** buf)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstAutoConvert *autoconvert = GST_AUTO_CONVERT (gst_pad_get_parent (pad));
  GstPad *internal_srcpad;

  g_return_val_if_fail (autoconvert != NULL, GST_FLOW_ERROR);

  internal_srcpad = gst_auto_convert_get_internal_srcpad (autoconvert);
  if (internal_srcpad) {
    ret = gst_pad_alloc_buffer (internal_srcpad, offset, size, caps, buf);
    gst_object_unref (internal_srcpad);
  } else

    *buf = NULL;

  gst_object_unref (autoconvert);

  return ret;
}
