gst_registry_scan_path (GstRegistry * registry, const gchar * path)
{
  GstRegistryScanContext context;
  gboolean result;

  g_return_val_if_fail (GST_IS_REGISTRY (registry), FALSE);
  g_return_val_if_fail (path != NULL, FALSE);

  init_scan_context (&context, registry);

  result = gst_registry_scan_path_internal (&context, path);

  clear_scan_context (&context);
  result |= context.changed;

  return result;
}
