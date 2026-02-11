connection_identified (TpStreamTubeChannel *self,
    GSocketConnection *conn,
    TpHandle handle,
    guint connection_id)
{
  TpStreamTubeConnection *tube_conn;

  tube_conn = _tp_stream_tube_connection_new (conn, self);

  g_hash_table_insert (self->priv->tube_connections,
      GUINT_TO_POINTER (connection_id), tube_conn);

  g_object_weak_ref (G_OBJECT (tube_conn), remote_connection_destroyed_cb,
      self);

  if (can_identify_contact (self))
    {
      TpConnection *connection;
      GArray *features;

      connection = tp_channel_get_connection (TP_CHANNEL (self));
      features = tp_simple_client_factory_dup_contact_features (
          tp_proxy_get_factory (connection), connection);


      G_GNUC_BEGIN_IGNORE_DEPRECATIONS

      tp_connection_get_contacts_by_handle (connection,
          1, &handle,
          features->len, (TpContactFeature *) features->data,
          _new_remote_connection_with_contact,
          tube_conn, g_object_unref, G_OBJECT (self));
       G_GNUC_END_IGNORE_DEPRECATIONS

      g_array_unref (features);
    }
  else
    {
      g_signal_emit (self, _signals[INCOMING], 0, tube_conn);

      g_object_unref (tube_conn);
    }
}
