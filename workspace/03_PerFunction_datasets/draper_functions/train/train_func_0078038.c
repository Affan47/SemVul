getNumRecipients(const SignalLocation &sender) const
{
  SignalMap::const_iterator findIter = m_signals.find(sender);
  if (findIter == m_signals.end()) {
    return 0;
  } else {
    return findIter->second.size();
  }
}
