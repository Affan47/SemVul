server_loop(int server, client * clients, int max_clients, service_credentials * credentials, int ncredentials)
{
  struct timeval timeout;
  int max_fd;
  client *c;
  fd_set readers, writers, readable, writable;

  max_fd  = server;

  FD_ZERO(&readers);
  FD_ZERO(&writers);
  FD_SET(server, &readers);

  g_running = 1;

  while(g_running)
  {
    int i, nfds;

    timeout.tv_sec  = 1;
    timeout.tv_usec = 0;

    readable = readers;
    writable = writers;

    nfds = select(max_fd + 1, &readable, &writable, NULL, &timeout);

    if ( nfds <= 0 ) continue;

    if (FD_ISSET(server, &readable))
      handle_connect(server, &clients, &max_clients, &max_fd, &readers);

    for ( i = 0 ; i < max_clients ; i++ )
    {
      c = (clients + i);
      if (c->socket == -1) continue;
      if (FD_ISSET(c->socket, &writable)) handle_write(c, &readers, &writers);
      if (FD_ISSET(c->socket, &readable)) handle_read(server, c, &readers, &writers, credentials, ncredentials);
    }
  }
}
