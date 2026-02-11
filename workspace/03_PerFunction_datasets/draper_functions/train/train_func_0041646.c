g_daemon_file_enumerate_children (GFile      *file,
				  const char *attributes,
				  GFileQueryInfoFlags flags,
				  GCancellable *cancellable,
				  GError **error)
{
  char *obj_path;
  char *path;
  GDaemonFileEnumerator *enumerator;
  GDBusConnection *connection;
  char *uri;
  GVfsDBusMount *proxy;
  gboolean res;
  GError *local_error = NULL;

  proxy = create_proxy_for_file (file, NULL, &path, &connection, cancellable, error);
  if (proxy == NULL)
    return NULL;

  enumerator = g_daemon_file_enumerator_new (file, proxy, attributes, TRUE);

  obj_path = g_daemon_file_enumerator_get_object_path (enumerator);
  uri = g_file_get_uri (file);

  res = gvfs_dbus_mount_call_enumerate_sync (proxy,
                                             path,
                                             obj_path,
                                             attributes ? attributes : "",
                                             flags,
                                             uri,
                                             cancellable,
                                             &local_error);

  if (! res)
    {
      if (g_error_matches (local_error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
        _g_dbus_send_cancelled_sync (g_dbus_proxy_get_connection (G_DBUS_PROXY (proxy)));
      _g_propagate_error_stripped (error, local_error);
    }

  g_free (path);
  g_free (uri);
  g_free (obj_path);
  g_object_unref (proxy);

  if (! res)
    goto out;

  g_daemon_file_enumerator_set_sync_connection (enumerator, connection);

  return G_FILE_ENUMERATOR (enumerator);

out:
  g_clear_object (&enumerator);
  return NULL;
}
