RemoveAll()
{
  while (m_hypos.begin() != m_hypos.end()) {
    Remove(m_hypos.begin());
  }
}
