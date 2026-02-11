connect(char* hostname, char* port) {
   if (endPoint != CLIENT)
      return false;

   SOCKET client;

   if (OpenClientSocket(&client, hostname, port, IPV4, TCP) == -1)
      return false;

   this->setFD(client);

   return true;
}
