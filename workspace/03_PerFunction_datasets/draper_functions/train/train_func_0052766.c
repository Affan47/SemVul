addCTime(const QString &path, const QByteArray& resource, quint32 ctime)
{
    assert(!path.isEmpty());
    m_hash.insert(key(path, resource), ctime );
}
