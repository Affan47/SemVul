WriteBits(UINT32 aValue, UINT32 aNumBits)
{
  while(aNumBits > 0)
  {
    UINT32 aNumNewBits = MyMin(aNumBits, m_BitPos);
    aNumBits -= aNumNewBits;

    UINT32 aMask = (1 << aNumNewBits) - 1;
    m_CurByte |= (aValue & aMask) << (8 - m_BitPos);
    aValue >>= aNumNewBits;

    m_BitPos -= aNumNewBits;

    if (m_BitPos == 0)
    {
      m_Stream.WriteByte(m_CurByte);
      m_BitPos = 8;
      m_CurByte = 0;
    }
  }
}
