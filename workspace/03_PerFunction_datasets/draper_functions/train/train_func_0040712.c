gst_shape_wipe_reset (GstShapeWipe * self)
{
  GST_DEBUG_OBJECT (self, "Resetting internal state");

  if (self->mask)
    gst_buffer_unref (self->mask);
  self->mask = NULL;

  g_mutex_lock (self->mask_mutex);
  g_cond_signal (self->mask_cond);
  g_mutex_unlock (self->mask_mutex);

  self->fmt = GST_VIDEO_FORMAT_UNKNOWN;
  self->width = self->height = 0;
  self->mask_bpp = 0;

  gst_segment_init (&self->segment, GST_FORMAT_TIME);

  gst_shape_wipe_reset_qos (self);
  self->frame_duration = 0;
}
