load(QDataStream &str)
{
    QString key;
    quint32 ctime;
    while(true)
    {
        KSycocaEntry::read(str, key);
        str >> ctime;
        if (key.isEmpty()) break;
        m_hash.insert(key, ctime);
    }
}
