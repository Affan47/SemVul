gst_registry_scan_path_internal (GstRegistryScanContext * context,
    const gchar * path)
{
  gboolean changed;

  GST_DEBUG_OBJECT (context->registry, "scanning path %s", path);
  changed = gst_registry_scan_path_level (context, path, 10);

  GST_DEBUG_OBJECT (context->registry, "registry changed in path %s: %d", path,
      changed);
  return changed;
}
