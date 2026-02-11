async_proxy_create_free (AsyncProxyCreate *data)
{
  g_clear_object (&data->mount);
  g_clear_object (&data->result);
  g_clear_object (&data->cancellable);
  g_clear_object (&data->mount_operation);
  g_clear_object (&data->connection);
  g_clear_object (&data->proxy);
  g_free (data);
}
