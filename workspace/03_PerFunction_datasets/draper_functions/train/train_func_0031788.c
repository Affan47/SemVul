inf_tcp_connection_new(InfIo* io,
                       InfIpAddress* remote_addr,
                       guint remote_port)
{
  InfTcpConnection* tcp;

  g_return_val_if_fail(INF_IS_IO(io), NULL);
  g_return_val_if_fail(remote_addr != NULL, NULL);
  g_return_val_if_fail(remote_port <= 65535, NULL);

  tcp = INF_TCP_CONNECTION(
    g_object_new(
      INF_TYPE_TCP_CONNECTION,
      "io", io,
      "remote-address", remote_addr,
      "remote-port", remote_port,
      NULL));

  return tcp;
}
