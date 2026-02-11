NET_RecvRaw(int sock, void *buffer, int length)
{


   int nrecv, n;
   char *buf = (char *)buffer;

   if (sock < 0) return -1;
   for (n = 0; n < length; n += nrecv) {
      while ((nrecv = recv(sock, buf+n, length-n, 0)) == -1 && errno == EINTR)
	errno = 0;
      if (nrecv < 0)
         return nrecv;
      else if (nrecv == 0)
	break;
   }

   return n;
}
