gst_subtitle_overlay_src_proxy_chain (GstPad * proxypad, GstBuffer * buffer)
{
  GstPad *ghostpad;
  GstSubtitleOverlay *self;
  GstFlowReturn ret;

  ghostpad = GST_PAD_CAST (gst_pad_get_parent (proxypad));
  if (G_UNLIKELY (!ghostpad)) {
    gst_buffer_unref (buffer);
    return GST_FLOW_ERROR;
  }
  self = GST_SUBTITLE_OVERLAY_CAST (gst_pad_get_parent (ghostpad));
  if (G_UNLIKELY (!self || self->srcpad != ghostpad)) {
    gst_buffer_unref (buffer);
    gst_object_unref (ghostpad);
    return GST_FLOW_ERROR;
  }

  ret = gst_proxy_pad_chain_default (proxypad, buffer);

  if (IS_VIDEO_CHAIN_IGNORE_ERROR (ret)) {
    GST_ERROR_OBJECT (self, "Downstream chain error: %s",
        gst_flow_get_name (ret));
    self->downstream_chain_error = TRUE;
  }

  gst_object_unref (self);
  gst_object_unref (ghostpad);

  return ret;
}
