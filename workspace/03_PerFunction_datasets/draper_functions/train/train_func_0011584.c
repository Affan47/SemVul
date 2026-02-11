g_tcp_socket_server_accept (g_tcp_socket* socket)
{
  int sockfd;
  struct sockaddr sa;
  socklen_t n;
  fd_set fdset;
  g_tcp_socket* s;

  if( socket == NULL )
     return NULL;

 try_again:

  FD_ZERO(&fdset);
  FD_SET(socket->sockfd, &fdset);

  if (select(socket->sockfd + 1, &fdset, NULL, NULL, NULL) == -1)
    {
      if (errno == EINTR)
   goto try_again;

      return NULL;
    }

  n = sizeof(s->sa);

  if ((sockfd = accept(socket->sockfd, &sa, &n)) == -1)
    {
      if (errno == EWOULDBLOCK ||
     errno == ECONNABORTED ||
#ifdef EPROTO
     errno == EPROTO ||
#endif
     errno == EINTR)
   goto try_again;

      return NULL;
    }

  s = malloc( sizeof(g_tcp_socket) );
  memset( s, 0, sizeof(g_tcp_socket));
  s->ref_count = 1;
  s->sockfd = sockfd;
  memcpy(&s->sa, &sa, sizeof(s->sa));

  return s;
}
