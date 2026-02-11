gearman_connection_create_args(gearman_universal_st& universal,
                                                      const char *host, in_port_t port)
{
  gearman_connection_st *connection= gearman_connection_create(universal, NULL);
  if (connection)
  {
    connection->set_host(host, port);

    if (gearman_failed(connection->lookup()))
    {
      gearman_gerror(universal, GEARMAN_GETADDRINFO);
      delete connection;
      return NULL;
    }
  }

  return connection;
}
