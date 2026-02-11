example_call_manager_close_all (ExampleCallManager *self)
{
  if (self->priv->channels != NULL)
    {
      GHashTable *tmp = self->priv->channels;
      GHashTableIter iter;
      gpointer v;

      self->priv->channels = NULL;

      g_hash_table_iter_init (&iter, tmp);

      while (g_hash_table_iter_next (&iter, NULL, &v))
        tp_base_channel_close (v);

      g_hash_table_unref (tmp);
    }

  if (self->priv->available_id != 0)
    {
      g_signal_handler_disconnect (self->priv->conn,
          self->priv->available_id);
      self->priv->available_id = 0;
    }

  if (self->priv->status_changed_id != 0)
    {
      g_signal_handler_disconnect (self->priv->conn,
          self->priv->status_changed_id);
      self->priv->status_changed_id = 0;
    }
}
