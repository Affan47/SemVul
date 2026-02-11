SendPDU (ISNS_CMD * cmd, int len)
{
   int e;
   fd_set read_set;
   struct timeval timeout;
   int nb;


   if (tcpFlag)
   {

      e = send (fd, (char *)cmd, len, 0);
      if (e < 0)
      {
         printf ("Error Sending TCP request.\n");
         return (-1);
      }

   }
   else
   {
      e = sendto (fd, (char *) cmd, len, 0, res->ai_addr, res->ai_addrlen);
      if (e < 0)
      {
         printf ("Error Sending UDP request.\n");
         return (e);
      }


      FD_ZERO(&read_set);
      FD_SET(fd, &read_set);
      timeout.tv_sec = 5;
      timeout.tv_usec = 0;

      nb = select(fd+1, &read_set, NULL, NULL, &timeout);
      if (nb < 0 )
          printf ("Error setting up socket\n");

      if (nb == 0)
      {
        printf ("Unable to connect - timedout\n");
        exit (-1);
      }

   }
   return (e);
}
