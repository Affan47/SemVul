CodeReal(ISequentialInStream *anInStream, ISequentialOutStream *anOutStream, const UINT64 *anInSize)
{
  if (!m_Created)
  {
    RETURN_IF_NOT_S_OK(Create());
    m_Created = true;
  }

  UINT64 aNowPos = 0;
  m_FinderPos = 0;

  RETURN_IF_NOT_S_OK(m_MatchFinder.Init(anInStream));
  m_OutStream.Init(anOutStream);
  m_ReverseOutStream.Init(&m_OutStream);

  InitStructures();

  while(true)
  {
    int aCurrentPassIndex = 0;
    bool aNoMoreBytes;
    while (true)
    {
      while(true)
      {
        aNoMoreBytes = (m_AdditionalOffset == 0 && m_MatchFinder.GetNumAvailableBytes() == 0);

        if (((m_CurrentBlockUncompressedSize >= kBlockUncompressedSizeThreshold ||
                 m_ValueIndex >= kValueBlockSize) &&
              (m_OptimumEndIndex == m_OptimumCurrentIndex))
            || aNoMoreBytes)
          break;
        UINT32 aPos;
        UINT32 aLen = GetOptimal(aPos);
        if (aLen >= kMatchMinLen)
        {
          UINT32 aNewLen = aLen - kMatchMinLen;
          m_Values[m_ValueIndex].Flag = kFlagLenPos;
          m_Values[m_ValueIndex].Len = BYTE(aNewLen);
          UINT32 aLenSlot = g_LenSlots[aNewLen];
          m_MainCoder.AddSymbol(kMatchNumber + aLenSlot);
          m_Values[m_ValueIndex].Pos = UINT16(aPos);
          UINT32 aPosSlot = GetPosSlot(aPos);
          m_DistCoder.AddSymbol(aPosSlot);
        }
        else if (aLen == 1)
        {
          BYTE aByte = m_MatchFinder.GetIndexByte(0 - m_AdditionalOffset);
          aLen = 1;
          m_MainCoder.AddSymbol(aByte);
          m_Values[m_ValueIndex].Flag = kFlagImm;
          m_Values[m_ValueIndex].Imm = aByte;
        }
        else
          throw E_INTERNAL_ERROR;
        m_ValueIndex++;
        m_AdditionalOffset -= aLen;
        aNowPos += aLen;
        m_CurrentBlockUncompressedSize += aLen;

      }
      aCurrentPassIndex++;
      bool aWriteMode = (aCurrentPassIndex == m_NumPasses);
      WriteBlockData(aWriteMode, aNoMoreBytes);
      if (aWriteMode)
        break;
      aNowPos = m_BlockStartPostion;
      m_AdditionalOffset = UINT32(m_FinderPos - m_BlockStartPostion);
      m_CurrentBlockUncompressedSize = 0;
    }
    m_BlockStartPostion += m_CurrentBlockUncompressedSize;
    m_CurrentBlockUncompressedSize = 0;
    if (aNoMoreBytes)
      break;
  }
  return  m_OutStream.Flush();
}
