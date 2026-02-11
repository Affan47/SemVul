feed_clam(int port, buffer *message) {
  struct sockaddr_in addr;
  int sockfd, r, addr_len;
  int yes = 1;
  long sent = 0;
  long size = strlen(message->data);
  char *host = _ds_read_attribute(agent_config, "ClamAVHost");

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    LOG(LOG_ERR, "socket(AF_INET, SOCK_STREAM, 0): %s", strerror(errno));
    return EFAILURE;
  }
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host);
  addr.sin_port = htons(port);
  addr_len = sizeof(struct sockaddr_in);
  LOGDEBUG("Connecting to %s:%d for virus stream transmission", host, port);
  if(connect(sockfd, (struct sockaddr *)&addr, addr_len)<0) {
    LOG(LOG_ERR, ERR_CLIENT_CONNECT_HOST, host, port, strerror(errno));
    close(sockfd);
    return EFAILURE;
  }

  setsockopt(sockfd,SOL_SOCKET,TCP_NODELAY,&yes,sizeof(int));

  while(sent<size) {
    r = send(sockfd, message->data+sent, size-sent, 0);
    if (r <= 0) {
      close(sockfd);
      return r;
    }
    sent += r;
  }

  close(sockfd);
  return 0;
}
