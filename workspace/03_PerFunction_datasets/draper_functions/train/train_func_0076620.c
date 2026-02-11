id() const
{
    QString guid = m_item.guid();
    if (!guid.isEmpty())
        return guid;

    return QString::fromLatin1("hash:%1").arg(calcMD5Sum(title()
            + description() + link() + content()));
}
