spd_open(const char* client_name, const char* connection_name, const char* user_name)
{
  struct sockaddr_in address;
  int connection;
  char *set_client_name;
  char* conn_name;
  char* usr_name;
  char *env_port;
  int port;
  int ret;
  char tcp_no_delay = 1;

  if (client_name == NULL) return -1;

  usr_name = strdup(user_name);

  if(connection_name == NULL)
      conn_name = strdup("main");
  else
      conn_name = strdup(connection_name);

  env_port = getenv("SPEECHD_PORT");
  if (env_port != NULL)
      port = strtol(env_port, NULL, 10);
  else
      port = SPEECHD_DEFAULT_PORT;


  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(port);
  address.sin_family = AF_INET;
  connection = socket(AF_INET, SOCK_STREAM, 0);


  ret = connect(connection, (struct sockaddr *)&address, sizeof(address));
  if (ret == -1){
      DBG("Error: Can't connect to server: %s", strerror(errno));
      return 0;
  }

  setsockopt(connection, IPPROTO_TCP, TCP_NODELAY, &tcp_no_delay, sizeof(int));

  set_client_name = g_strdup_printf("SET SELF CLIENT_NAME \"%s:%s:%s\"", usr_name,
          client_name, conn_name);

  ret = spd_execute_command(connection, set_client_name);

  spd__free(usr_name);
  spd__free(conn_name);
  spd__free(set_client_name);

  return connection;
}
