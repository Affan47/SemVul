evd_buffered_output_stream_flush_async (GOutputStream       *stream,
                                        gint                 io_priority,
                                        GCancellable        *cancellable,
                                        GAsyncReadyCallback  callback,
                                        gpointer             user_data)
{
  EvdBufferedOutputStream *self = EVD_BUFFERED_OUTPUT_STREAM (stream);
  GError *error = NULL;

  if (! evd_buffered_output_stream_flush (stream, cancellable, &error))
    {
      GSimpleAsyncResult *res;

      res = g_simple_async_result_new_from_error (G_OBJECT (self),
                                                  callback,
                                                  user_data,
                                                  error);
      g_simple_async_result_complete_in_idle (res);
      g_object_unref (res);

      g_error_free (error);

      return;
    }

  self->priv->async_result =
    g_simple_async_result_new (G_OBJECT (self),
                               callback,
                               user_data,
                               evd_buffered_output_stream_flush_async);

  if (self->priv->buffer->len > 0)
    self->priv->flushing = TRUE;
  else
    evd_buffered_output_stream_flush_base_stream (self, cancellable);
}
