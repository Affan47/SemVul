gst_subtitle_overlay_video_sink_chain (GstPad * pad, GstBuffer * buffer)
{
  GstSubtitleOverlay *self = GST_SUBTITLE_OVERLAY (GST_PAD_PARENT (pad));
  GstFlowReturn ret = gst_proxy_pad_chain_default (pad, buffer);

  if (G_UNLIKELY (self->downstream_chain_error) || self->passthrough_identity) {
    return ret;
  } else if (IS_VIDEO_CHAIN_IGNORE_ERROR (ret)) {
    GST_DEBUG_OBJECT (self, "Subtitle renderer produced chain error: %s",
        gst_flow_get_name (ret));
    GST_SUBTITLE_OVERLAY_LOCK (self);
    self->subtitle_error = TRUE;
    gst_pad_set_blocked_async_full (self->subtitle_block_pad, TRUE,
        _pad_blocked_cb, self, NULL);

    gst_pad_set_blocked_async_full (self->video_block_pad, TRUE,
        _pad_blocked_cb, self, NULL);
    GST_SUBTITLE_OVERLAY_UNLOCK (self);

    return GST_FLOW_OK;
  }

  return ret;
}
