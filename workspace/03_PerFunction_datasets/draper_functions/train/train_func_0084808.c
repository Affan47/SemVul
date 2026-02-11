onACK(const int32_t& ack)
{
   int64_t B = 0;
   double inc = 0;

   uint64_t currtime = CTimer::getTime();
   if (currtime - m_LastRCTime < (uint64_t)m_iRCInterval)
      return;

   m_LastRCTime = currtime;

   if (m_bSlowStart)
   {
      m_dCWndSize += CSeqNo::seqlen(m_iLastAck, ack);
      m_iLastAck = ack;

      if (m_dCWndSize > m_dMaxCWndSize)
      {
         m_bSlowStart = false;
         if (m_iRcvRate > 0)
            m_dPktSndPeriod = 1000000.0 / m_iRcvRate;
         else
            m_dPktSndPeriod = m_dCWndSize / (m_iRTT + m_iRCInterval);
      }
   }
   else
      m_dCWndSize = m_iRcvRate / 1000000.0 * (m_iRTT + m_iRCInterval) + 16;


   if (m_bSlowStart)
      goto RATE_LIMIT;

   if (m_bLoss)
   {
      m_bLoss = false;
      goto RATE_LIMIT;
   }

   B = (int64_t)(m_iBandwidth - 1000000.0 / m_dPktSndPeriod);
   if ((m_dPktSndPeriod > m_dLastDecPeriod) && ((m_iBandwidth / 9) < B))
      B = m_iBandwidth / 9;
   if (B <= 0)
      inc = 1.0 / m_iMSS;
   else
   {


      inc = pow(10.0, ceil(log10(B * m_iMSS * 8.0))) * 0.0000015 / m_iMSS;

      if (inc < 1.0/m_iMSS)
         inc = 1.0/m_iMSS;
   }

   m_dPktSndPeriod = (m_dPktSndPeriod * m_iRCInterval) / (m_dPktSndPeriod * inc + m_iRCInterval);


RATE_LIMIT:

   if ((NULL != m_pcParam) && (m_iPSize == 8))
   {
      int64_t maxSR = *(int64_t*)m_pcParam;
      if (maxSR <= 0)
         return;

      double minSP = 1000000.0 / (double(maxSR) / m_iMSS);
      if (m_dPktSndPeriod < minSP)
         m_dPktSndPeriod = minSP;
   }
}
