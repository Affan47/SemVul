ProcessUnaligned(vector<string> &toksTarget, vector<string> &toksSource
                                , const std::vector<bool> &m_sourceAligned, const std::vector<bool> &m_targetAligned)
{
  const string *nullWord = m_vocab.GetOrAdd("NULL");

  for (size_t pos = 0; pos < m_sourceAligned.size(); ++pos)
  {
    bool isAlignedCurr = m_sourceAligned[pos];
    if (!isAlignedCurr)
    {
      const string &tmpWord = toksSource[pos];
      const string *sourceWord = m_vocab.GetOrAdd(tmpWord);

      Process(nullWord, sourceWord);
    }
  }

  for (size_t pos = 0; pos < m_targetAligned.size(); ++pos)
  {
    bool isAlignedCurr = m_targetAligned[pos];
    if (!isAlignedCurr)
    {
      const string &tmpWord = toksTarget[pos];
      const string *targetWord = m_vocab.GetOrAdd(tmpWord);

      Process(targetWord, nullWord);
    }
  }

}
