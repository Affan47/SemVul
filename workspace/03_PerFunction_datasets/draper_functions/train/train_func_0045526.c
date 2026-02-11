inf_tcp_connection_connected(InfTcpConnection* connection)
{
  InfTcpConnectionPrivate* priv;
  priv = INF_TCP_CONNECTION_PRIVATE(connection);

  priv->status = INF_TCP_CONNECTION_CONNECTED;
  priv->front_pos = 0;
  priv->back_pos = 0;

  priv->events = INF_IO_INCOMING | INF_IO_ERROR;

  if(priv->watch == NULL)
  {
    priv->watch = inf_io_add_watch(
      priv->io,
      &priv->socket,
      priv->events,
      inf_tcp_connection_io,
      connection,
      NULL
    );
  }
  else
  {
    inf_io_update_watch(priv->io, priv->watch, priv->events);
  }

  g_object_freeze_notify(G_OBJECT(connection));
  g_object_notify(G_OBJECT(connection), "status");
  g_object_notify(G_OBJECT(connection), "local-address");
  g_object_notify(G_OBJECT(connection), "local-port");
  g_object_thaw_notify(G_OBJECT(connection));
}
