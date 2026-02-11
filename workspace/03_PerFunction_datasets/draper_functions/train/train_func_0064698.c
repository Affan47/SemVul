connection_shutdown_finished_cb (TpBaseConnection *conn,
                                 gpointer data)
{
  TpBaseConnectionManager *self = TP_BASE_CONNECTION_MANAGER (data);
  TpBaseConnectionManagerPrivate *priv = self->priv;


  g_object_ref (self);

  g_assert (g_hash_table_lookup (priv->connections, conn));
  g_hash_table_remove (priv->connections, conn);

  DEBUG ("dereferenced connection");
  if (g_hash_table_size (priv->connections) == 0)
    {
      g_signal_emit (self, signals[NO_MORE_CONNECTIONS], 0);
    }

  g_signal_handlers_disconnect_by_func (conn,
      connection_shutdown_finished_cb, data);

  g_object_unref (conn);
  g_object_unref (self);
}
