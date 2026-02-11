redis_connect(char *host, char *port)
{
  struct addrinfo hints;
  struct addrinfo *servinfo;
  struct addrinfo *p;
  int    optval = 1;
  REDIS  *redis;
  char   *servername;
  char   *serverport;
  void   *addr;
  int    rc;

  redis = (REDIS*) malloc(sizeof(REDIS));
  if (redis == NULL)
  {
    _redis_setMallocError();
    return NULL;
  }

  redis->port = NULL;
  servername = host ? host
                    : "127.0.0.1";
  serverport = port ? port
                    : "6379";
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;


  rc = getaddrinfo(servername, serverport, &hints, &servinfo);
  if ( rc != 0)
  {
    _redis_free(redis);
    _redis_setCnxError(REDIS_ERROR_CNX_GAI, rc);
    return NULL;
  }


  for (p = servinfo; p != NULL; p = p->ai_next)
  {
    redis->fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if (redis->fd == -1)
    {
      _redis_setCnxError(REDIS_ERROR_CNX_SOCKET, errno);
      continue;
    }


    if (setsockopt(redis->fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval) == -1||
        setsockopt(redis->fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval) == -1)
    {
      freeaddrinfo(servinfo);
      _redis_free(redis);
      _redis_setCnxError(REDIS_ERROR_CNX_SOCKET, errno);
      return NULL;
    }
    if (connect(redis->fd, p->ai_addr, p->ai_addrlen) == -1)
      _redis_setCnxError(REDIS_ERROR_CNX_CONNECT, errno);
    else
      break;
  }


  if (p == NULL)
  {
    freeaddrinfo(servinfo);
    _redis_free(redis);
    return NULL;
  }


  if (p->ai_family == AF_INET)
  {
    struct sockaddr_in *ipv4;
    ipv4 = (struct sockaddr_in *)p->ai_addr;
    addr = &(ipv4->sin_addr);
  }
  else
  {
    struct sockaddr_in6 *ipv6;
    ipv6 = (struct sockaddr_in6 *)p->ai_addr;
    addr = &(ipv6->sin6_addr);
  }

  redis->port = malloc(sizeof(serverport));

  if (redis->host == NULL || redis->port == NULL)
  {
    _redis_setMallocError();
    freeaddrinfo(servinfo);
    _redis_free(redis);
    return NULL;
  }


  inet_ntop(p->ai_family, addr, redis->host, sizeof(redis->host));
  strcpy(redis->port, serverport);
  freeaddrinfo(servinfo);
  return redis;
}
