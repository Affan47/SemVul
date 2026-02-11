gst_deinterlace_update_passthrough (GstDeinterlace * self)
{
  if (self->mode == GST_DEINTERLACE_MODE_DISABLED)
    self->passthrough = TRUE;
  else if (!GST_VIDEO_INFO_IS_INTERLACED (&self->vinfo)
      && self->mode != GST_DEINTERLACE_MODE_INTERLACED)
    self->passthrough = TRUE;
  else
    self->passthrough = FALSE;

  GST_DEBUG_OBJECT (self, "Passthrough: %d", self->passthrough);
}
