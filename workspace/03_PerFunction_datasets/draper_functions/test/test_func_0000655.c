create_proxy_for_file_async (GFile *file,
                             GCancellable *cancellable,
                             GAsyncReadyCallback op_callback,
                             gpointer op_callback_data,
                             CreateProxyAsyncCallback callback,
                             gpointer callback_data,
                             GDestroyNotify notify)
{
  GDaemonFile *daemon_file = G_DAEMON_FILE (file);
  AsyncProxyCreate *data;

  data = g_new0 (AsyncProxyCreate, 1);

  data->result = g_simple_async_result_new (G_OBJECT (file),
                                            op_callback, op_callback_data,
                                            NULL);

  data->file = g_object_ref (file);
  if (cancellable)
    data->cancellable = g_object_ref (cancellable);
  data->callback = callback;
  data->callback_data = callback_data;
  data->notify = notify;

  _g_daemon_vfs_get_mount_info_async (daemon_file->mount_spec,
                                      daemon_file->path,
                                      async_got_mount_info,
                                      data);
}
