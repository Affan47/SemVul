addData(CUnit* unit, int offset)
{
   int pos = (m_iLastAckPos + offset) % m_iSize;
   if (offset > m_iMaxPos)
      m_iMaxPos = offset;

   if (NULL != m_pUnit[pos])
      return -1;

   m_pUnit[pos] = unit;

   unit->m_iFlag = 1;
   ++ m_pUnitQueue->m_iCount;

   return 0;
}
