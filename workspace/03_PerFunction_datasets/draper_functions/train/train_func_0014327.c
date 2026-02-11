Init(ISequentialInStream *anInStream, ISequentialOutStream *anOutStream)
{
  CBaseCoder::Init();

  RETURN_IF_NOT_S_OK(m_MatchFinder.Init(anInStream));
  m_RangeEncoder.Init(anOutStream);

  int i;
  for(i = 0; i < kNumStates; i++)
  {
    for (INT j = 0; j <= m_PosStateMask; j++)
    {
      m_MainChoiceEncoders[i][j].Init();
      m_MatchRepShortChoiceEncoders[i][j].Init();
    }
    m_MatchChoiceEncoders[i].Init();
    m_MatchRepChoiceEncoders[i].Init();
    m_MatchRep1ChoiceEncoders[i].Init();
    m_MatchRep2ChoiceEncoders[i].Init();
  }

  m_LiteralEncoder.Init();

  for(i = 0; i < kNumLenToPosStates; i++)
    m_PosSlotEncoder[i].Init();

  for(i = 0; i < kNumPosModels; i++)
    m_PosEncoders[i].Init();

  m_LenEncoder.Init();
  m_RepMatchLenEncoder.Init();

  m_PosAlignEncoder.Init();

  m_LongestMatchWasFound = false;
  m_OptimumEndIndex = 0;
  m_OptimumCurrentIndex = 0;
  m_AdditionalOffset = 0;

  return S_OK;
}
