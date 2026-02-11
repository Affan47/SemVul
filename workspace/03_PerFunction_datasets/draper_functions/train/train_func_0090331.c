open_sock (int port)
{
  struct sockaddr_in servadr;
  int server_handle;
  int O_on = 1;

  if ((server_handle = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    exit_fatal ("Error opening socket Abort !");
  if (setsockopt (server_handle, SOL_SOCKET, SO_REUSEADDR,
		  &O_on, sizeof (int)) == -1)
    exit_fatal ("Setting reused address fail Abort !");

  initaddr (&servadr,NULL, port);
  if (bind
      (server_handle, (struct sockaddr *) &servadr,
       sizeof (struct sockaddr)) == -1)
    exit_fatal ("error bind socket");

  if (listen (server_handle, MAXCONNECT) == -1)
    exit_fatal ("Damned errors when listen Abort !");
  return server_handle;
}
