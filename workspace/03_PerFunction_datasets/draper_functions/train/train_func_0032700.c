gst_subtitle_overlay_subtitle_sink_setcaps (GstPad * pad, GstCaps * caps)
{
  GstSubtitleOverlay *self = GST_SUBTITLE_OVERLAY (gst_pad_get_parent (pad));
  gboolean ret = TRUE;
  GstPad *target = NULL;;

  GST_DEBUG_OBJECT (pad, "Setting caps: %" GST_PTR_FORMAT, caps);

  target =
      gst_ghost_pad_get_target (GST_GHOST_PAD_CAST (self->subtitle_sinkpad));

  GST_SUBTITLE_OVERLAY_LOCK (self);
  gst_caps_replace (&self->subcaps, caps);

  if (target && gst_pad_accept_caps (target, caps)) {
    GST_DEBUG_OBJECT (pad, "Target accepts caps");
    ret = gst_ghost_pad_setcaps_default (pad, caps);
    GST_SUBTITLE_OVERLAY_UNLOCK (self);
    goto out;
  }

  GST_DEBUG_OBJECT (pad, "Target did not accept caps");

  self->subtitle_error = FALSE;

  gst_pad_set_blocked_async_full (self->subtitle_block_pad, TRUE,
      _pad_blocked_cb, self, NULL);

  gst_pad_set_blocked_async_full (self->video_block_pad, TRUE,
      _pad_blocked_cb, self, NULL);
  GST_SUBTITLE_OVERLAY_UNLOCK (self);

out:
  if (target)
    gst_object_unref (target);
  gst_object_unref (self);
  return ret;
}
