open_connection_async_cb (GObject *source_object,
                          GAsyncResult *res,
                          gpointer user_data)
{
  GVfsDBusDaemon *proxy;
  AsyncDBusCall *async_call = user_data;
  GError *error = NULL;

  proxy = gvfs_dbus_daemon_proxy_new_finish (res, &error);
  if (proxy == NULL)
    {
      async_call->io_error = g_error_copy (error);
      g_error_free (error);
      async_call_finish (async_call);
      return;
    }

  g_dbus_proxy_set_default_timeout (G_DBUS_PROXY (proxy), G_VFS_DBUS_TIMEOUT_MSECS);

  gvfs_dbus_daemon_call_get_connection (proxy,
                                        async_call->cancellable,
                                        (GAsyncReadyCallback) async_get_connection_response,
                                        async_call);

  g_object_unref (proxy);
}
