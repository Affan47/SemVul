match(const QString& text) const
{
    if (m_exactPatterns.contains(text))
    {
        return true;
    }

    for (QStringList::const_iterator it(m_startPatterns.begin()),
                                     itEnd(m_startPatterns.end());
         it != itEnd; ++it)
    {
        if (text.startsWith(*it))
        {
            return true;
        }
    }

    for (QStringList::const_iterator it(m_endPatterns.begin()),
                                     itEnd(m_endPatterns.end());
         it != itEnd; ++it)
    {
        if (text.endsWith(*it))
        {
            return true;
        }
    }

    for (QList<QByteArray>::const_iterator it(m_generalPatterns.begin()),
                                           itEnd(m_generalPatterns.end());
         it != itEnd; ++it)
    {
        if (::fnmatch(*it, text.toLocal8Bit(), FNM_PATHNAME) == 0)
        {
            return true;
        }
    }

    return false;
}
