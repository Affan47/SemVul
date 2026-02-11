tcp_connect(const char *host, const char *serv)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;


  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0) {
    syslog(LOG_ERR, "tcp_connect error for %s, %s", host, serv);
  }

  ressave = res;


  do {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue;

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;

   close(sockfd);
  } while ( (res = res->ai_next) != NULL);

  if (res == NULL) {
    syslog(LOG_ERR, "tcp_connect error for %s, %s", host, serv);
  }

  freeaddrinfo(ressave);
  return (sockfd);
}
