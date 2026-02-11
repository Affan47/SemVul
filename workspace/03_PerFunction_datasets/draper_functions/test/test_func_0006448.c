tp_file_transfer_channel_accept_file_async (TpFileTransferChannel *self,
    GFile *file,
    guint64 offset,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_return_if_fail (TP_IS_FILE_TRANSFER_CHANNEL (self));
  g_return_if_fail (G_IS_FILE (file));

  if (self->priv->access_control_param != NULL)
    {
      g_simple_async_report_error_in_idle (G_OBJECT (self), callback,
          user_data, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
          "Can't accept already accepted transfer");

      return;
    }

  if (self->priv->state != TP_FILE_TRANSFER_STATE_PENDING)
    {
      g_simple_async_report_error_in_idle (G_OBJECT (self), callback,
          user_data, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
          "Can't accept a transfer that isn't pending");

      return;
    }

  if (tp_channel_get_requested (TP_CHANNEL (self)))
    {
      g_simple_async_report_error_in_idle (G_OBJECT (self), callback,
          user_data, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
          "Can't accept outgoing transfer");

      return;
    }

  self->priv->result = g_simple_async_result_new (G_OBJECT (self), callback,
      user_data, tp_file_transfer_channel_accept_file_async);

  self->priv->requested_offset = offset;

  g_file_replace_async (file, NULL, FALSE, G_FILE_CREATE_NONE,
      G_PRIORITY_DEFAULT, NULL, file_replace_async_cb, self);
}
