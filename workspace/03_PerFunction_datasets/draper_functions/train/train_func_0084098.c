propertyNames() const
{
    QStringList res = m_mapProps.keys();
    res.append( QString::fromLatin1("Name") );
    res.append( QString::fromLatin1("Comment") );
    return res;
}
