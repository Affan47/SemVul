evd_buffered_input_stream_read_str_async (EvdBufferedInputStream *self,
                                          gsize                   size,
                                          int                     io_priority,
                                          GCancellable           *cancellable,
                                          GAsyncReadyCallback     callback,
                                          gpointer                user_data)
{
  g_return_if_fail (EVD_IS_BUFFERED_INPUT_STREAM (self));

  self->priv->async_buffer = g_new0 (gchar, size + 1);

  g_input_stream_read_async (G_INPUT_STREAM (self),
                             self->priv->async_buffer,
                             size,
                             io_priority,
                             cancellable,
                             callback,
                             user_data);
}
