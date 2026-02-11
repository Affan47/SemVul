cph_iface_object_skeleton_new (const gchar *object_path)
{
  g_return_val_if_fail (g_variant_is_object_path (object_path), NULL);
  return CPH_IFACE_OBJECT_SKELETON (g_object_new (CPH_IFACE_TYPE_OBJECT_SKELETON, "g-object-path", object_path, NULL));
}
