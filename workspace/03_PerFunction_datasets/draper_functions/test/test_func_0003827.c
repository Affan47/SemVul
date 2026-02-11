new_network_connection(char *hostname, int port) {
  Network_connection *result;
  int sockfd = -1, ret = -1;
  struct addrinfo req, *ans, *tmpaddr;
  char name[NI_MAXHOST], portname[NI_MAXSERV];


  memset(&req, 0, sizeof(req));
  req.ai_flags = 0;
  req.ai_family = AF_UNSPEC;
  req.ai_socktype = SOCK_STREAM;
  req.ai_protocol = IPPROTO_TCP;

  if (getaddrinfo(hostname, NULL, &req, &ans) != 0) {
    NETDEBUG("getaddrinfo failed: %s", strerror(errno));
    return NULL;
  }

  tmpaddr = ans;
  while (tmpaddr != NULL) {
    ((struct sockaddr_in *) tmpaddr->ai_addr)->sin_port = htons(port);
    getnameinfo(tmpaddr->ai_addr, tmpaddr->ai_addrlen,
                name, sizeof(name), portname, sizeof(portname),
                NI_NUMERICHOST | NI_NUMERICSERV);

    NETDEBUG( "Trying %s port %s...", name, portname);

    sockfd =
      socket(tmpaddr->ai_family, tmpaddr->ai_socktype, tmpaddr->ai_protocol);
    if (sockfd < 0) {
      NETDEBUG("socket failed: %s", strerror(errno));
    } else if ((ret = connect(sockfd, tmpaddr->ai_addr, tmpaddr->ai_addrlen))
               < 0) {
      NETDEBUG( "connect failed: %s", strerror(errno));
    } else
      break;

    tmpaddr = tmpaddr->ai_next;
  }

  if (ret != 0 || sockfd < 0) {
    freeaddrinfo(ans);
    return NULL;
  }
  NETDEBUG("succeeded");

  result = init_network_connection();
  result->fd = sockfd;

  freeaddrinfo(ans);

  return result;
}
