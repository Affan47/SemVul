getPktRcvSpeed() const
{

   std::copy(m_piPktWindow, m_piPktWindow + m_iAWSize - 1, m_piPktReplica);
   std::nth_element(m_piPktReplica, m_piPktReplica + (m_iAWSize / 2), m_piPktReplica + m_iAWSize - 1);
   int median = m_piPktReplica[m_iAWSize / 2];

   int count = 0;
   int sum = 0;
   int upper = median << 3;
   int lower = median >> 3;


   int* p = m_piPktWindow;
   for (int i = 0, n = m_iAWSize; i < n; ++ i)
   {
      if ((*p < upper) && (*p > lower))
      {
         ++ count;
         sum += *p;
      }
      ++ p;
   }


   if (count > (m_iAWSize >> 1))
      return (int)ceil(1000000.0 / (sum / count));
   else
      return 0;
}
