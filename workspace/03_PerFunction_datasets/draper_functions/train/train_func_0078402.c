getsockname(const UDTSOCKET u, sockaddr* name, int* namelen)
{
   CUDTSocket* s = locate(u);

   if (NULL == s)
      throw CUDTException(5, 4, 0);

   if (s->m_pUDT->m_bBroken)
      throw CUDTException(5, 4, 0);

   if (INIT == s->m_Status)
      throw CUDTException(2, 2, 0);

   if (AF_INET == s->m_iIPversion)
      *namelen = sizeof(sockaddr_in);
   else
      *namelen = sizeof(sockaddr_in6);


   memcpy(name, s->m_pSelfAddr, *namelen);

   return 0;
}
