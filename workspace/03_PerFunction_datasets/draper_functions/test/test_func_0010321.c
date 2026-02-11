gst_shape_wipe_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstShapeWipe *self = GST_SHAPE_WIPE (object);

  switch (prop_id) {
    case PROP_POSITION:{
      gfloat f = g_value_get_float (value);

      GST_LOG_OBJECT (self, "Setting mask position: %f", f);
      self->mask_position = f;
      break;
    }
    case PROP_BORDER:{
      gfloat f = g_value_get_float (value);

      GST_LOG_OBJECT (self, "Setting mask border: %f", f);
      self->mask_border = f;
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
