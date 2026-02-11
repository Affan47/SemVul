tp_connection_disconnect_async (TpConnection *self,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *result;

  g_return_if_fail (TP_IS_CONNECTION (self));

  result = g_simple_async_result_new (G_OBJECT (self), callback,
      user_data, tp_connection_disconnect_async);

  tp_cli_connection_call_disconnect (self, -1, _tp_connection_void_cb, result,
      NULL, NULL);
}
