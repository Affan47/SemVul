Load(const std::vector<FactorType> &input
                                  , const std::vector<FactorType> &output
                                  , const std::string &filePath
				  , const std::vector<float> &weight
                                  , size_t tableLimit
                                  , const LMList& languageModels
                                  , const WordPenaltyProducer* wpProducer)
{
  PrintUserTime("Start loading binary SCFG phrase table. ");

  m_languageModels = &(languageModels);
  m_wpProducer = wpProducer;
  m_filePath = filePath;
  m_tableLimit = tableLimit;
  m_inputFactorsVec		= input;
  m_outputFactorsVec	= output;

  LoadTargetLookup();

  if (!m_dbWrapper.BeginLoad(filePath))
    return false;

  CHECK(m_dbWrapper.GetMisc("Version") == OnDiskPt::OnDiskWrapper::VERSION_NUM);
  CHECK(m_dbWrapper.GetMisc("NumSourceFactors") == input.size());
  CHECK(m_dbWrapper.GetMisc("NumTargetFactors") == output.size());
  CHECK(m_dbWrapper.GetMisc("NumScores") == weight.size());

  return true;
}
