getServerIndex(const QString &url) const
{
    for (int i = 0; i < m_Servers.count(); i++)
        if (m_Servers.at(i).url() == url)
            return i;
    return -1;
}
