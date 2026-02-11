ensure_texture_pixel_aspect_ratio (ClutterGstVideoSink * sink)
{
  ClutterGstVideoSinkPrivate *priv = sink->priv;
  GParamSpec *pspec;
  GValue par = { 0, };

  if (priv->texture == NULL)
    return;

  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (priv->texture),
      "pixel-aspect-ratio");
  if (pspec) {
    g_value_init (&par, GST_TYPE_FRACTION);
    gst_value_set_fraction (&par, priv->info.par_n, priv->info.par_d);
    g_object_set_property (G_OBJECT (priv->texture),
        "pixel-aspect-ratio", &par);
    g_value_unset (&par);
  }
}
