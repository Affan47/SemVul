equals(const PhraseAlignment& lhs, const PhraseAlignment& rhs) const
{
  return m_domain.getDomainOfSentence(lhs.sentenceId) ==
    m_domain.getDomainOfSentence( rhs.sentenceId);
}
