gst_text_overlay_video_bufferalloc (GstPad * pad, guint64 offset, guint size,
    GstCaps * caps, GstBuffer ** buffer)
{
  GstTextOverlay *overlay = GST_TEXT_OVERLAY (gst_pad_get_parent (pad));
  GstFlowReturn ret = GST_FLOW_WRONG_STATE;
  GstPad *allocpad;

  if (G_UNLIKELY (!overlay))
    return GST_FLOW_WRONG_STATE;

  GST_OBJECT_LOCK (overlay);
  allocpad = overlay->srcpad ? gst_object_ref (overlay->srcpad) : NULL;
  GST_OBJECT_UNLOCK (overlay);

  if (allocpad) {
    ret = gst_pad_alloc_buffer (allocpad, offset, size, caps, buffer);
    gst_object_unref (allocpad);
  }

  gst_object_unref (overlay);
  return ret;
}
