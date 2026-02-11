gst_jpeg_dec_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstJpegDec *dec;

  dec = GST_JPEG_DEC (object);

  switch (prop_id) {
    case PROP_IDCT_METHOD:
      dec->idct_method = g_value_get_enum (value);
      break;
    case PROP_MAX_ERRORS:
      g_atomic_int_set (&dec->max_errors, g_value_get_int (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
