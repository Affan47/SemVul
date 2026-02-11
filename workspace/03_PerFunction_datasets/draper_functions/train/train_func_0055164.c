make_connection_unix(char *address)
{
  struct sockaddr_un	ps;
  int len;
  int sd;

  ps.sun_family = PF_UNIX;
  strcpy(ps.sun_path, address);
  len = sizeof(ps.sun_family) + strlen(ps.sun_path);

  if((sd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0){
    jlog("Error: server-client: failed to create socket\n");
    return -1;
  }
  while(connect(sd, (struct sockaddr *)&ps, len) < 0){
    jlog("Error: server-client: failed to conect to %s\n", address);

    jlog("Error: server-client: retry after %d sec...\n",CONNECTION_RETRY_INTERVAL);
    sleep(CONNECTION_RETRY_INTERVAL);
  }

  jlog("Stat: server-client: connected to unix socket %s\n", address);

  return sd;
}
