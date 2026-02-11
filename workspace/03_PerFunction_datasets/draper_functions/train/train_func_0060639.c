updateMux(CUDTSocket* s, const CUDTSocket* ls)
{
   CGuard cg(m_ControlLock);

   int port = (AF_INET == ls->m_iIPversion) ? ntohs(((sockaddr_in*)ls->m_pSelfAddr)->sin_port) : ntohs(((sockaddr_in6*)ls->m_pSelfAddr)->sin6_port);


   for (map<int, CMultiplexer>::iterator i = m_mMultiplexer.begin(); i != m_mMultiplexer.end(); ++ i)
   {
      if (i->second.m_iPort == port)
      {

         ++ i->second.m_iRefCount;
         s->m_pUDT->m_pSndQueue = i->second.m_pSndQueue;
         s->m_pUDT->m_pRcvQueue = i->second.m_pRcvQueue;
         s->m_iMuxID = i->second.m_iID;
         return;
      }
   }
}
