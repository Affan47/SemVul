remove(const UDTSOCKET& id)
{
   CGuard vg(m_RIDVectorLock);

   for (list<CRL>::iterator i = m_lRendezvousID.begin(); i != m_lRendezvousID.end(); ++ i)
   {
      if (i->m_iID == id)
      {
         if (AF_INET == i->m_iIPversion)
            delete (sockaddr_in*)i->m_pPeerAddr;
         else
            delete (sockaddr_in6*)i->m_pPeerAddr;

         m_lRendezvousID.erase(i);

         return;
      }
   }
}
