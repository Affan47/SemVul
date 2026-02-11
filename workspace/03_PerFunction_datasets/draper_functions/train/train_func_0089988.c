CreateRuleLookupManager(
  const InputType &sentence,
  const ChartCellCollectionBase &cellCollection)
{
  return new ChartRuleLookupManagerOnDisk(sentence, cellCollection, *this,
                                          m_dbWrapper, m_languageModels,
                                          m_wpProducer, m_inputFactorsVec,
                                          m_outputFactorsVec, m_filePath);
}
