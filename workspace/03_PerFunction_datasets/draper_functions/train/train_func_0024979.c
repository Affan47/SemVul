tp_channel_dispatch_operation_dispose (GObject *object)
{
  TpChannelDispatchOperation *self = TP_CHANNEL_DISPATCH_OPERATION (object);
  void (*dispose) (GObject *) =
    G_OBJECT_CLASS (tp_channel_dispatch_operation_parent_class)->dispose;

  if (self->priv->connection != NULL)
    {
      g_object_unref (self->priv->connection);
      self->priv->connection = NULL;
    }

  if (self->priv->account != NULL)
    {
      g_object_unref (self->priv->account);
      self->priv->account = NULL;
    }

  if (self->priv->channels != NULL)
    {

      g_ptr_array_unref (self->priv->channels);
      self->priv->channels = NULL;
    }

  g_strfreev (self->priv->possible_handlers);
  self->priv->possible_handlers = NULL;

  if (self->priv->immutable_properties != NULL)
    {
      g_hash_table_unref (self->priv->immutable_properties);
      self->priv->immutable_properties = NULL;
    }

  if (dispose != NULL)
    dispose (object);
}
