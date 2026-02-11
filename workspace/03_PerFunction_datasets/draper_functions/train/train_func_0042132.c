async_got_connection_cb (GDBusConnection *connection,
                         GError *io_error,
                         gpointer callback_data)
{
  AsyncPathCall *data = callback_data;

  if (connection == NULL)
    {
      g_dbus_error_strip_remote_error (io_error);
      g_simple_async_result_set_from_error (data->result, io_error);
      _g_simple_async_result_complete_with_cancellable (data->result, data->cancellable);
      async_path_call_free (data);
      return;
    }

  data->connection = g_object_ref (connection);
  gvfs_dbus_mount_proxy_new (connection,
                             G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES | G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS,
                             data->mount_info->dbus_id,
                             data->mount_info->object_path,
                             data->cancellable,
                             async_proxy_new_cb,
                             data);
}
