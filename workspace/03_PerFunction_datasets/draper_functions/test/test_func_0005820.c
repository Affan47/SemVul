gst_chroma_hold_set_caps (GstBaseTransform * btrans,
    GstCaps * incaps, GstCaps * outcaps)
{
  GstChromaHold *self = GST_CHROMA_HOLD (btrans);

  GST_CHROMA_HOLD_LOCK (self);

  if (!gst_video_format_parse_caps (outcaps, &self->format,
          &self->width, &self->height)) {
    GST_WARNING_OBJECT (self,
        "Failed to parse caps %" GST_PTR_FORMAT " -> %" GST_PTR_FORMAT, incaps,
        outcaps);
    GST_CHROMA_HOLD_UNLOCK (self);
    return FALSE;
  }

  GST_DEBUG_OBJECT (self,
      "Setting caps %" GST_PTR_FORMAT " -> %" GST_PTR_FORMAT, incaps, outcaps);

  if (!gst_chroma_hold_set_process_function (self)) {
    GST_WARNING_OBJECT (self, "No processing function for this caps");
    GST_CHROMA_HOLD_UNLOCK (self);
    return FALSE;
  }

  GST_CHROMA_HOLD_UNLOCK (self);

  return TRUE;
}
