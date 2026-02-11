BeginLoad(const std::string &filePath)
{
  if (!OpenForLoad(filePath))
    return false;

  if (!m_vocab.Load(*this))
    return false;

  UINT64 rootFilePos = GetMisc("RootNodeOffset");
  m_rootSourceNode = new PhraseNode(rootFilePos, *this);

  return true;
}
