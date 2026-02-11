GNUNET_CLIENT_connect (const char *service_name,
                       const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  struct GNUNET_CLIENT_Connection *client;
  struct GNUNET_CONNECTION_Handle *connection;

  if (GNUNET_OK !=
      test_service_configuration (service_name,
				  cfg))
    return NULL;
  connection = do_connect (service_name, cfg, 0);
  client = GNUNET_malloc (sizeof (struct GNUNET_CLIENT_Connection));
  client->attempts = 1;
  client->connection = connection;
  client->service_name = GNUNET_strdup (service_name);
  client->cfg = cfg;
  client->back_off = GNUNET_TIME_UNIT_MILLISECONDS;
  return client;
}
