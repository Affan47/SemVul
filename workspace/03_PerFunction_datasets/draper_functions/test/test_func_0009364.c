language() const
{
    if (m_strings.isEmpty()) return QString();

    const QStringList langs = KGlobal::locale()->languageList();
    for (QStringList::ConstIterator it = langs.begin(); it != langs.end(); ++it)
        if (m_strings.contains(*it)) return (*it);

    if (m_strings.contains(QString())) return QString();
    else return m_strings.begin().key();
}
