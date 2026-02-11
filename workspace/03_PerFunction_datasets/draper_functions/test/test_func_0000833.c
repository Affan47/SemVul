createFirstChain(const QString &identifier)
{
    DesktopChain value(m_currentChain.value());
    m_chains.erase(m_currentChain);
    m_currentChain = m_chains.insert(identifier, value);
}
