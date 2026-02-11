tpaw_connection_managers_prepare_async (
    TpawConnectionManagers *self,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *result;

  result = g_simple_async_result_new (G_OBJECT (managers),
      callback, user_data, tpaw_connection_managers_prepare_finish);

  if (self->priv->ready)
    {
      g_simple_async_result_complete_in_idle (result);
      g_object_unref (result);
      return;
    }

  g_signal_connect (self, "notify::ready", G_CALLBACK (notify_ready_cb),
      result);
}
