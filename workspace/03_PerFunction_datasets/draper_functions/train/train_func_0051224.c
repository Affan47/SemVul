gst_interleave_finalize (GObject * object)
{
  GstInterleave *self = GST_INTERLEAVE (object);

  if (self->collect) {
    gst_object_unref (self->collect);
    self->collect = NULL;
  }

  if (self->channel_positions
      && self->channel_positions != self->input_channel_positions) {
    g_value_array_free (self->channel_positions);
    self->channel_positions = NULL;
  }

  if (self->input_channel_positions) {
    g_value_array_free (self->input_channel_positions);
    self->input_channel_positions = NULL;
  }

  gst_caps_replace (&self->sinkcaps, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
