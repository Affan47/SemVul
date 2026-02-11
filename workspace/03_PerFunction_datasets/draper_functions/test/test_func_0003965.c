start_server(cmd_args *args)
{
  client                 *clients = NULL;
  int                    server;
  int                    max_clients      = 1, cur_clients = 0;
  service_credentials   *credentials      = NULL;
  int                    ncredentials     = 0;

  getpw_log(LOG_TRACE, "Initialising clients list");
  init_clients(&clients, cur_clients, max_clients);
  getpw_log(LOG_TRACE, "Loading passwords file");
  sc_load(args->password_file, &credentials, &ncredentials);
  if ( ncredentials == 0 )
  {
    getpw_log(LOG_FATAL, "Couldn't load any passwords from %s!", args->password_file);
    return -1;
  }
  getpw_log(LOG_INFO, "Loaded %d passwords", ncredentials);
  getpw_log(LOG_TRACE, "Creating server socket on port %d", args->port);
  server = setup_server_socket(args->port);
  getpw_log(LOG_INFO, "getpw server (%lu) listening on port %d", getpid(), args->port);
  server_loop(server, clients, max_clients, credentials, ncredentials);
  getpw_log(LOG_WARNING, "getpw server shutting down");
  close(server);

  return 0;
}
