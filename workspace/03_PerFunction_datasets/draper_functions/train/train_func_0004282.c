tp_handle_channels_context_dispose (GObject *object)
{
  TpHandleChannelsContext *self = TP_HANDLE_CHANNELS_CONTEXT (
      object);
  void (*dispose) (GObject *) =
    G_OBJECT_CLASS (tp_handle_channels_context_parent_class)->dispose;

  if (self->priv->state == TP_HANDLE_CHANNELS_CONTEXT_STATE_NONE ||
      self->priv->state == TP_HANDLE_CHANNELS_CONTEXT_STATE_DELAYED)
    {
      GError error = { TP_ERROR, TP_ERROR_NOT_IMPLEMENTED,
          "Disposing the TpHandleChannelsContext" };

      WARNING ("Disposing a context in the %s state",
          self->priv->state == TP_HANDLE_CHANNELS_CONTEXT_STATE_NONE ?
          "none": "delayed");

      tp_handle_channels_context_fail (self, &error);
    }

  if (self->account != NULL)
    {
      g_object_unref (self->account);
      self->account = NULL;
    }

  if (self->connection != NULL)
    {
      g_object_unref (self->connection);
      self->connection = NULL;
    }

  if (self->channels != NULL)
    {
      g_ptr_array_unref (self->channels);
      self->channels = NULL;
    }

  if (self->requests_satisfied != NULL)
    {
      g_ptr_array_foreach (self->requests_satisfied, (GFunc) g_object_unref,
          NULL);
      g_ptr_array_unref (self->requests_satisfied);
      self->requests_satisfied = NULL;
    }

  if (self->handler_info != NULL)
    {
      g_hash_table_unref (self->handler_info);
      self->handler_info = NULL;
    }

  if (self->priv->result != NULL)
    {
      g_object_unref (self->priv->result);
      self->priv->result = NULL;
    }

  if (dispose != NULL)
    dispose (object);
}
