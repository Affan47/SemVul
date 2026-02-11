recvfile(fstream& ofs, int64_t& offset, const int64_t& size, const int& block)
{
   if (UDT_DGRAM == m_iSockType)
      throw CUDTException(5, 10, 0);

   if (!m_bConnected)
      throw CUDTException(2, 2, 0);
   else if ((m_bBroken || m_bClosing) && (0 == m_pRcvBuffer->getRcvDataSize()))
      throw CUDTException(2, 1, 0);

   if (size <= 0)
      return 0;

   CGuard recvguard(m_RecvLock);

   int64_t torecv = size;
   int unitsize = block;
   int recvsize;


   try
   {
      ofs.seekp((streamoff)offset);
   }
   catch (...)
   {
      throw CUDTException(4, 3);
   }


   while (torecv > 0)
   {
      if (ofs.fail())
      {

         int32_t err_code = CUDTException::EFILE;
         sendCtrl(8, &err_code);

         throw CUDTException(4, 4);
      }

      #ifndef WIN32
         pthread_mutex_lock(&m_RecvDataLock);
         while (!m_bBroken && m_bConnected && !m_bClosing && (0 == m_pRcvBuffer->getRcvDataSize()))
            pthread_cond_wait(&m_RecvDataCond, &m_RecvDataLock);
         pthread_mutex_unlock(&m_RecvDataLock);
      #else
         while (!m_bBroken && m_bConnected && !m_bClosing && (0 == m_pRcvBuffer->getRcvDataSize()))
            WaitForSingleObject(m_RecvDataCond, INFINITE);
      #endif

      if (!m_bConnected)
         throw CUDTException(2, 2, 0);
      else if ((m_bBroken || m_bClosing) && (0 == m_pRcvBuffer->getRcvDataSize()))
         throw CUDTException(2, 1, 0);

      unitsize = int((torecv >= block) ? block : torecv);
      recvsize = m_pRcvBuffer->readBufferToFile(ofs, unitsize);

      if (recvsize > 0)
      {
         torecv -= recvsize;
         offset += recvsize;
      }
   }

   if (m_pRcvBuffer->getRcvDataSize() <= 0)
   {

      s_UDTUnited.m_EPoll.disable_read(m_SocketID, m_sPollID);
   }

   return size - torecv;
}
