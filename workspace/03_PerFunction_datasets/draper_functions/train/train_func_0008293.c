q330SeedSend(void *seed_record)
{
  char  *errmsg;
  char  inbuffer[8192];


  if (bFirst)
  {
    if ((errmsg = LoopRecordSize(&iSeedRecordSize)) != NULL)
      return errmsg;
    if ((errmsg = LogServerPort(&iLogPort)) != NULL)
      return errmsg;
    bFirst = 1;
  }


  if (iSocket < 0)
  {
    struct sockaddr_in serv_addr;
    struct hostent *server;


    iSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (iSocket < 0)
    {
      sprintf(errmsgbuf, "socket call error %d, %s",
        errno, strerror(errno));
      return errmsgbuf;
    }


    server = gethostbyname("localhost");
    if (server == NULL)
    {
      close(iSocket);
      iSocket = -1;
      return ("gethostbyname failed to find 'localhost'");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(iLogPort);


    if (connect(iSocket, (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0)
    {
      close(iSocket);
      iSocket = -1;
      return "Unable to connect to archd";
    }
  }


  if (send(iSocket, seed_record, iSeedRecordSize, 0) != iSeedRecordSize)
  {
    sprintf(errmsgbuf, "send archd failed, errno %d %s",
      errno, strerror(errno));
    close(iSocket);
    iSocket = -1;
    return errmsgbuf;
  }


  if (recv(iSocket, inbuffer, 1, MSG_WAITALL) != 1)
  {
    sprintf(errmsgbuf, "recv archd failed, errno %d %s",
      errno, strerror(errno));
    close(iSocket);
    iSocket = -1;
    return errmsgbuf;
  }
  return NULL;
}
