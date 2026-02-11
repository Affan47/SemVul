file_transfer_set_uri_cb (TpProxy *proxy,
    const GError *uri_error,
    gpointer user_data,
    GObject *weak_object)
{
  TpFileTransferChannel *self = TP_FILE_TRANSFER_CHANNEL (weak_object);

  if (uri_error != NULL)
    {
      DEBUG ("Failed to set FileTransfer.URI: %s", uri_error->message);

    }

  if (!set_address_and_access_control (self))
    return;


  tp_cli_channel_type_file_transfer_call_accept_file (TP_CHANNEL (self), -1,
      self->priv->socket_type,
      self->priv->access_control,
      self->priv->access_control_param,
      self->priv->requested_offset,
      accept_or_provide_file_cb,
      NULL,
      NULL,
      G_OBJECT (self));
}
