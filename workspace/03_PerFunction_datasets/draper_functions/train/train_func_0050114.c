has_virus(buffer *message) {
  struct sockaddr_in addr;
  int sockfd;
  int virus = 0;
  int yes = 1;
  int port = atoi(_ds_read_attribute(agent_config, "ClamAVPort"));
  int addr_len;
  char *host = _ds_read_attribute(agent_config, "ClamAVHost");
  FILE *sock;
  FILE *sockout;
  char buf[128];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    LOG(LOG_ERR, "socket(AF_INET, SOCK_STREAM, 0): %s", strerror(errno));
    return 0;
  }
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host);
  addr.sin_port = htons(port);
  addr_len = sizeof(struct sockaddr_in);
  LOGDEBUG("Connecting to %s:%d for virus check", host, port);
  if(connect(sockfd, (struct sockaddr *)&addr, addr_len)<0) {
    LOG(LOG_ERR, ERR_CLIENT_CONNECT_HOST, host, port, strerror(errno));
    close(sockfd);
    return 0;
  }

  setsockopt(sockfd,SOL_SOCKET,TCP_NODELAY,&yes,sizeof(int));

  sock = fdopen(sockfd, "r");
  if (sock == NULL) {
    LOG(LOG_ERR, ERR_CLIENT_CONNECT_HOST, host, port, strerror(errno));
    close(sockfd);
    return 0;
  }
  sockout = fdopen(sockfd, "w");
  if (sockout == NULL) {
    LOG(LOG_ERR, ERR_CLIENT_CONNECT_HOST, host, port, strerror(errno));
    fclose(sock);
    close(sockfd);
    return 0;
  }
  fprintf(sockout, "STREAM\r\n");
  fflush(sockout);

  if ((fgets(buf, sizeof(buf), sock))!=NULL && !strncmp(buf, "PORT", 4)) {
    int s_port = atoi(buf+5);
    if (feed_clam(s_port, message)==0) {
      if ((fgets(buf, sizeof(buf), sock))!=NULL) {
        if (!strstr(buf, ": OK"))
          virus = 1;
      }
    }
  }
  fclose(sock);
  fclose(sockout);
  close(sockfd);

  return virus;
}
