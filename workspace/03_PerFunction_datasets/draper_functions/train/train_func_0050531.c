nxtnet_cli_connect(const char *hostname,int port,const char *password) {
  nxtnet_cli_t *cli;
  struct hostent *hent;
  struct sockaddr_in server;
  int sock;


  sock = socket(AF_INET,SOCK_STREAM,0);
  if (sock==-1) return NULL;


  hent = gethostbyname(hostname);
  if (hent==NULL) {
    close(sock);
    return NULL;
  }


  memcpy(&server.sin_addr,hent->h_addr_list[0],hent->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  if (connect(sock,(struct sockaddr *)&server,sizeof(server))<0) {
    close(sock);
    return NULL;
  }


  cli = malloc(sizeof(nxtnet_cli_t));
  memset(cli,0,sizeof(nxtnet_cli_t));
  cli->sock = sock;
  cli->buf = malloc(NXTNET_BUFSIZE);
  if (password!=NULL) strncpy(cli->password,password,NXTNET_PWD_LEN);

  return cli;
}
