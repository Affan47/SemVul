recvmsg(char* data, const int& len)
{
   if (UDT_STREAM == m_iSockType)
      throw CUDTException(5, 9, 0);


   if (!m_bConnected)
      throw CUDTException(2, 2, 0);

   if (len <= 0)
      return 0;

   CGuard recvguard(m_RecvLock);

   if (m_bBroken || m_bClosing)
   {
      int res = m_pRcvBuffer->readMsg(data, len);

      if (m_pRcvBuffer->getRcvMsgNum() <= 0)
      {

         s_UDTUnited.m_EPoll.disable_read(m_SocketID, m_sPollID);
      }

      if (0 == res)
         throw CUDTException(2, 1, 0);
      else
         return res;
   }

   if (!m_bSynRecving)
   {
      int res = m_pRcvBuffer->readMsg(data, len);
      if (0 == res)
         throw CUDTException(6, 2, 0);
      else
         return res;
   }

   int res = 0;
   bool timeout = false;

   do
   {
      #ifndef WIN32
         pthread_mutex_lock(&m_RecvDataLock);

         if (m_iRcvTimeOut < 0)
         {
            while (!m_bBroken && m_bConnected && !m_bClosing && (0 == (res = m_pRcvBuffer->readMsg(data, len))))
               pthread_cond_wait(&m_RecvDataCond, &m_RecvDataLock);
         }
         else
         {
            uint64_t exptime = CTimer::getTime() + m_iRcvTimeOut * 1000ULL;
            timespec locktime;

            locktime.tv_sec = exptime / 1000000;
            locktime.tv_nsec = (exptime % 1000000) * 1000;

            if (pthread_cond_timedwait(&m_RecvDataCond, &m_RecvDataLock, &locktime) == ETIMEDOUT)
               timeout = true;

            res = m_pRcvBuffer->readMsg(data, len);
         }
         pthread_mutex_unlock(&m_RecvDataLock);
      #else
         if (m_iRcvTimeOut < 0)
         {
            while (!m_bBroken && m_bConnected && !m_bClosing && (0 == (res = m_pRcvBuffer->readMsg(data, len))))
               WaitForSingleObject(m_RecvDataCond, INFINITE);
         }
         else
         {
            if (WaitForSingleObject(m_RecvDataCond, DWORD(m_iRcvTimeOut)) == WAIT_TIMEOUT)
               timeout = true;

            res = m_pRcvBuffer->readMsg(data, len);
         }
      #endif

      if (m_bBroken || m_bClosing)
         throw CUDTException(2, 1, 0);
      else if (!m_bConnected)
         throw CUDTException(2, 2, 0);
   } while ((0 == res) && !timeout);

   if (m_pRcvBuffer->getRcvMsgNum() <= 0)
   {

      s_UDTUnited.m_EPoll.disable_read(m_SocketID, m_sPollID);
   }

   if ((res <= 0) && (m_iRcvTimeOut >= 0))
      throw CUDTException(6, 2, 0);

   return res;
}
