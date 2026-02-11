ListenAtTcpPort(int port)
{
  int sock;
  struct sockaddr_in addr;
  int one = 1;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (!initSockets())
    return -1;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    rfbClientErr("ListenAtTcpPort: socket\n");
    return -1;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
		 (const char *)&one, sizeof(one)) < 0) {
    rfbClientErr("ListenAtTcpPort: setsockopt\n");
    close(sock);
    return -1;
  }

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    rfbClientErr("ListenAtTcpPort: bind\n");
    close(sock);
    return -1;
  }

  if (listen(sock, 5) < 0) {
    rfbClientErr("ListenAtTcpPort: listen\n");
    close(sock);
    return -1;
  }

  return sock;
}
