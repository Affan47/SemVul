async_got_mount_info (GMountInfo *mount_info,
                      gpointer _data,
                      GError *error)
{
  AsyncProxyCreate *data = _data;

  if (error != NULL)
    {
      g_dbus_error_strip_remote_error (error);
      g_simple_async_result_set_from_error (data->result, error);
      _g_simple_async_result_complete_with_cancellable (data->result, data->cancellable);
      async_proxy_create_free (data);
      return;
    }

  data->mount_info = g_mount_info_ref (mount_info);

  _g_dbus_connection_get_for_async (mount_info->dbus_id,
                                    async_got_connection_cb,
                                    data,
                                    data->cancellable);
}
