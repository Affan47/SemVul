GetTranslationOptionList(size_t startPos, size_t endPos)
{
  size_t maxSize = endPos - startPos;
  size_t maxSizePhrase = StaticData::Instance().GetMaxPhraseLength();
  maxSize = std::min(maxSize, maxSizePhrase);

  CHECK(maxSize < m_collection[startPos].size());
  return m_collection[startPos][maxSize];
}
