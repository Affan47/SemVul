maxEndOffset() const
{
    if (!m_endContainer)
        return 0;
    if (!m_endContainer->offsetInCharacters())
        return m_endContainer->childNodeCount();
    return m_endContainer->maxCharacterOffset();
}
