requestConnection()
{
  if (connection) return;

  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) return;

  struct hostent *hp = gethostbyname("localhost");
  if (NULL == hp) return;

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = (unsigned short) htons(port);
  memcpy(&server.sin_addr, hp->h_addr, (size_t) hp->h_length);

  if (connect(s, (struct sockaddr *) & server, sizeof(server)) < 0)
  {
#ifdef HAVE_WINSOCK_H
    (void) shutdown(s,  1 );
    (void) closesocket(s);
#else
    (void) close(s);
#endif
    return;
  }
  connection = new DcmTCPConnection(s);
}
