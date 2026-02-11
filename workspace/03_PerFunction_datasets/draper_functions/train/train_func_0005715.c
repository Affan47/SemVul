getLostSeq()
{
   if (0 == m_iLength)
     return -1;

   CGuard listguard(m_ListLock);

   if (0 == m_iLength)
     return -1;

   if (m_iLastInsertPos == m_iHead)
      m_iLastInsertPos = -1;


   int32_t seqno = m_piData1[m_iHead];


   if (-1 == m_piData2[m_iHead])
   {

      m_piData1[m_iHead] = -1;
      m_iHead = m_piNext[m_iHead];
   }
   else
   {

      int loc = (m_iHead + 1) % m_iSize;

      m_piData1[loc] = CSeqNo::incseq(seqno);
      if (CSeqNo::seqcmp(m_piData2[m_iHead], m_piData1[loc]) > 0)
         m_piData2[loc] = m_piData2[m_iHead];

      m_piData1[m_iHead] = -1;
      m_piData2[m_iHead] = -1;

      m_piNext[loc] = m_piNext[m_iHead];
      m_iHead = loc;
   }

   m_iLength --;

   return seqno;
}
