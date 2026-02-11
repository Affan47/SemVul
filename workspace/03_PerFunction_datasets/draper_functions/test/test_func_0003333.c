evd_socket_connect_addr (EvdSocket           *self,
                         GSocketAddress      *address,
                         GCancellable        *cancellable,
                         GAsyncReadyCallback  callback,
                         gpointer             user_data)
{
  GError *error = NULL;

  g_return_if_fail (EVD_IS_SOCKET (self));

  if (! evd_socket_check_availability (self, &error) ||
      ! evd_socket_connect_addr_internal (self, address, &error))
    {
      evd_socket_deliver_async_result_error (self,
                                             NULL,
                                             error,
                                             callback,
                                             user_data,
                                             TRUE);
      return;
    }
  else
    {
      self->priv->has_pending = TRUE;
      self->priv->async_result = g_simple_async_result_new (G_OBJECT (self),
                                                            callback,
                                                            user_data,
                                                            evd_socket_connect_addr);
    }

  return;
}
