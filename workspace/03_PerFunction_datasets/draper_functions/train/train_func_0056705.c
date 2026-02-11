gst_square_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstSquare *square;
  GstGeometricTransform *gt;

  gt = GST_GEOMETRIC_TRANSFORM_CAST (object);
  square = GST_SQUARE_CAST (gt);

  switch (prop_id) {
    case PROP_WIDTH:
      g_value_set_double (value, square->width);
      break;
    case PROP_HEIGHT:
      g_value_set_double (value, square->height);
      break;
    case PROP_ZOOM:
      g_value_set_double (value, square->zoom);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
