ooSocketRecvFrom (OOSOCKET socket, ASN1OCTET* pbuf, ASN1UINT bufsize,
                      char* remotehost, ASN1UINT hostBufLen, int * remoteport)
{
   struct sockaddr_in m_addr;
   int len, addrlen;
   const char * host=NULL;
   if (socket == OOSOCKET_INVALID) return ASN_E_INVSOCKET;
   addrlen = sizeof(m_addr);

   memset (&m_addr, 0, sizeof (m_addr));

   if ((len = recvfrom (socket, (char*) pbuf, bufsize, 0,
                        (struct sockaddr*)&m_addr, (socklen_t *) &addrlen)) == -1)
      return ASN_E_INVSOCKET;

   if(remoteport)
      *remoteport = ntohs(m_addr.sin_port);
   if(remotehost)
   {
      host = ast_inet_ntoa(m_addr.sin_addr);
      if(strlen(host) < (hostBufLen-1))
         strcpy(remotehost, host);
      else
         return -1;
   }
   return len;
}
