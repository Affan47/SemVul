gst_photography_get_config (GstPhotography * photo,
    GstPhotographySettings * config)
{
  GstPhotographyInterface *iface;
  gboolean ret = FALSE;

  g_return_val_if_fail (photo != NULL, FALSE);

  iface = GST_PHOTOGRAPHY_GET_INTERFACE (photo);
  if (iface->get_config) {
    ret = iface->get_config (photo, config);
  }

  return ret;
}
