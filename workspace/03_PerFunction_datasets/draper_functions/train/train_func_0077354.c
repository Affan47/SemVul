gvfs_dbus_mount_call_mount_mountable_sync (
    GVfsDBusMount *proxy,
    const gchar *arg_path_data,
    const gchar *arg_dbus_id,
    const gchar *arg_obj_path,
    gboolean *out_is_uri,
    gchar **out_path,
    gboolean *out_must_mount_location,
    GVariant **out_mount_spec,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "MountMountable",
    g_variant_new ("(^ayso)",
                   arg_path_data,
                   arg_dbus_id,
                   arg_obj_path),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b^ayb@(aya{sv}))",
                 out_is_uri,
                 out_path,
                 out_must_mount_location,
                 out_mount_spec);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
