gst_multipart_mux_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GstMultipartMux *mux;

  mux = GST_MULTIPART_MUX (object);

  switch (prop_id) {
    case ARG_BOUNDARY:
      g_free (mux->boundary);
      mux->boundary = g_strdup (g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
