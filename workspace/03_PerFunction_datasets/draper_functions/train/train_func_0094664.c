accept() {
   if (endPoint != LISTENER)
      return NULL;

   SOCKET client;

   client = AcceptConnection(sock);

   if (client == -1)
      return NULL;

   TCPSocket* tcpClient = new TCPSocket(SERVER);
   if (!tcpClient->setFD(client)) {
      delete tcpClient;
      return NULL;
   }

   return tcpClient;
}
