client_socket_connected (TpStreamTubeChannel *self)
{
  GSocketConnection *conn;

  conn = g_socket_connection_factory_create_connection (
      self->priv->client_socket);
  g_assert (conn);

  DEBUG ("Stream Tube socket connected");

#ifdef HAVE_GIO_UNIX
  if (self->priv->access_control == TP_SOCKET_ACCESS_CONTROL_CREDENTIALS)
    {
      guchar byte;

      byte = g_value_get_uchar (self->priv->access_control_param);
      tp_unix_connection_send_credentials_with_byte_async (conn, byte, NULL,
          send_credentials_cb, self);
    }
#endif

  if (self->priv->local_conn_id_set)
    {
      new_local_connection_identified (self, conn, self->priv->local_conn_id);

      self->priv->local_conn_id_set = FALSE;
    }
  else
    {


      g_assert (self->priv->local_conn_waiting_id == NULL);
      self->priv->local_conn_waiting_id = g_object_ref (conn);
    }

  g_object_unref (conn);
}
