async_proxy_new_cb (GObject *source_object,
                    GAsyncResult *res,
                    gpointer user_data)
{
  AsyncProxyCreate *data = user_data;
  GDaemonFile *daemon_file = G_DAEMON_FILE (data->file);
  const char *path;
  GVfsDBusMount *proxy;
  GError *error = NULL;
  GSimpleAsyncResult *result;

  proxy = gvfs_dbus_mount_proxy_new_finish (res, &error);
  if (proxy == NULL)
    {
      _g_simple_async_result_take_error_stripped (data->result, error);
      _g_simple_async_result_complete_with_cancellable (data->result, data->cancellable);
      async_proxy_create_free (data);
      return;
    }

  data->proxy = proxy;


  g_dbus_proxy_set_default_timeout (G_DBUS_PROXY (data->proxy), G_MAXINT);

  path = g_mount_info_resolve_path (data->mount_info, daemon_file->path);


  result = data->result;
  g_object_weak_ref (G_OBJECT (result), (GWeakNotify)async_proxy_create_free, data);
  data->result = NULL;

  data->callback (proxy,
                  data->connection,
                  data->mount_info,
                  path,
                  result,
                  NULL,
                  data->cancellable,
                  data->callback_data);


  g_object_unref (result);
}
