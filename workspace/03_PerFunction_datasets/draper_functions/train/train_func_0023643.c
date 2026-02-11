acknowledge(const int32_t& seq, int32_t& ack)
{
   if (m_iHead >= m_iTail)
   {


      for (int i = m_iTail, n = m_iHead; i < n; ++ i)
      {

         if (seq == m_piACKSeqNo[i])
         {

            ack = m_piACK[i];


            int rtt = int(CTimer::getTime() - m_pTimeStamp[i]);

            if (i + 1 == m_iHead)
            {
               m_iTail = m_iHead = 0;
               m_piACKSeqNo[0] = -1;
            }
            else
               m_iTail = (i + 1) % m_iSize;

            return rtt;
         }
      }


      return -1;
   }


   for (int j = m_iTail, n = m_iHead + m_iSize; j < n; ++ j)
   {

      if (seq == m_piACKSeqNo[j % m_iSize])
      {

         j %= m_iSize;
         ack = m_piACK[j];


         int rtt = int(CTimer::getTime() - m_pTimeStamp[j]);

         if (j == m_iHead)
         {
            m_iTail = m_iHead = 0;
            m_piACKSeqNo[0] = -1;
         }
         else
            m_iTail = (j + 1) % m_iSize;

         return rtt;
      }
   }


   return -1;
}
