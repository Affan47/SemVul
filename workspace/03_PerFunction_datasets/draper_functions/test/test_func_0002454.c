checkPending() const
{
    if (!m_loadedHint)
        return;
    if (m_parent)
        m_parent->checkPending();
    else if (m_parentNode)
        m_parentNode->checkAddPendingSheet();
}
