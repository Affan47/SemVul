Load(const std::vector<FactorType> &input
                                 , const std::vector<FactorType> &output
                                 , const std::string &filePath
                                 , const std::vector<float> &weight
                                 , size_t tableLimit
                                 , const LMList &languageModels
                                 , const WordPenaltyProducer* wpProducer)
{
  const StaticData &staticData = StaticData::Instance();
  if (staticData.ThreadCount() > 1)
  {
    UserMessage::Add("Suffix array implementation is not threadsafe");
    return false;
  }


  SetFilePath(filePath);
  m_tableLimit = tableLimit;

  m_input = &input;
  m_output = &output;
  m_languageModels = &languageModels;
  m_wpProducer = wpProducer;
  m_weight = &weight;

  return true;
}
