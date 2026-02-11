gst_rnd_buffer_size_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstRndBufferSize *self = GST_RND_BUFFER_SIZE (object);

  switch (prop_id) {
    case ARG_SEED:
      self->seed = g_value_get_uint (value);
      break;
    case ARG_MINIMUM:
      self->min = g_value_get_int (value);
      break;
    case ARG_MAXIMUM:
      self->max = g_value_get_int (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
