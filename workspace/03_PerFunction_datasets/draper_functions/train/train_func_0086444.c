gst_uri_handler_get_uri_type (GstURIHandler * handler)
{
  GstURIHandlerInterface *iface;
  guint ret;

  g_return_val_if_fail (GST_IS_URI_HANDLER (handler), GST_URI_UNKNOWN);

  iface = GST_URI_HANDLER_GET_INTERFACE (handler);
  g_return_val_if_fail (iface != NULL, GST_URI_UNKNOWN);
  g_return_val_if_fail (iface->get_type != NULL
      || iface->get_type_full != NULL, GST_URI_UNKNOWN);

  if (iface->get_type != NULL)
    ret = iface->get_type ();
  else
    ret = iface->get_type_full (G_OBJECT_TYPE (handler));
  g_return_val_if_fail (GST_URI_TYPE_IS_VALID (ret), GST_URI_UNKNOWN);

  return ret;
}
