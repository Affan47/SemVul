lookup(const UDTSOCKET u)
{

   CGuard cg(m_ControlLock);

   map<UDTSOCKET, CUDTSocket*>::iterator i = m_Sockets.find(u);

   if ((i == m_Sockets.end()) || (i->second->m_Status == CLOSED))
      throw CUDTException(5, 4, 0);

   return i->second->m_pUDT;
}
