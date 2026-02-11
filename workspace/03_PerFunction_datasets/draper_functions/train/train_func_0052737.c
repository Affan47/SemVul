g_daemon_file_query_filesystem_info (GFile                *file,
				     const char           *attributes,
				     GCancellable         *cancellable,
				     GError              **error)
{
  GFileInfo *info;
  GVfsDBusMount *proxy;
  char *path;
  gboolean res;
  GVariant *iter_info;
  GError *local_error = NULL;

  proxy = create_proxy_for_file (file, NULL, &path, NULL, cancellable, error);
  if (proxy == NULL)
    return NULL;

  iter_info = NULL;
  res = gvfs_dbus_mount_call_query_filesystem_info_sync (proxy,
                                                         path,
                                                         attributes ? attributes : "",
                                                         &iter_info,
                                                         cancellable,
                                                         &local_error);

  if (! res)
    {
      if (g_error_matches (local_error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
        _g_dbus_send_cancelled_sync (g_dbus_proxy_get_connection (G_DBUS_PROXY (proxy)));
      _g_propagate_error_stripped (error, local_error);
    }

  g_free (path);
  g_object_unref (proxy);

  if (! res)
    return NULL;

  info = _g_dbus_get_file_info (iter_info, error);
  g_variant_unref (iter_info);

  return info;
}
