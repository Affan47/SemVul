ooSetFDSETs(struct pollfd *pfds, int *nfds)
{
   if(gH323ep.gkClient && gH323ep.gkClient->rasSocket != 0)
   {
      pfds[*nfds].fd = gH323ep.gkClient->rasSocket;
      pfds[*nfds].events = POLLIN;
      (*nfds)++;
   }
   if(gH323ep.listener)
   {
      pfds[*nfds].fd = *gH323ep.listener;
      pfds[*nfds].events = POLLIN;
      (*nfds)++;
   }

   return OO_OK;

}
