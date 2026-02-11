knocker_core_portscan_tcp_connnect (knocker_core_portscan_data_t * data, unsigned int port)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_portscan_tcp_connnect (...) called\n");
  fprintf (stderr, "debug: connecting to port: %d\n", port);
#endif

  if (knocker_core_open_socket (&data->socket, data->host.hostaddr.ss_family, PROTO_TCP) == KNOCKER_SOCKET_ERROR)
    {
#ifdef DEBUG
      fprintf (stderr, "debug: socket error, couldn't connect.\n");
#endif
      return -1;
    }

  memcpy (&(data->host.sockaddr_st), &(data->host.hostaddr), data->host.addrlen);
  switch (data->host.hostaddr.ss_family) {
    case AF_INET6:
      ((struct sockaddr_in6 *) &(data->host.sockaddr_st))->sin6_port = htons (port);
    case AF_INET:
    default:
      ((struct sockaddr_in *) &(data->host.sockaddr_st))->sin_port = htons (port);
  }

  if (!connect (data->socket.fd, (struct sockaddr *) &data->host.sockaddr_st, data->host.addrlen))

    {
      knocker_core_close_socket (&data->socket);
#ifdef DEBUG
      fprintf (stderr, "debug: connected to port: %d, port is open\n", port);
#endif
      return PORT_OPEN;
    }
#ifdef DEBUG
  fprintf (stderr, "debug: port: %d is closed\n", port);
#endif


  knocker_core_close_socket (&data->socket);

  return (PORT_CLOSED);
}
