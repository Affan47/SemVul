fromXml(const QString &fullPackConfigXml)
{
    QDomDocument doc;
    QString error;
    int line, col;
    if (!doc.setContent(fullPackConfigXml, &error, &line, &col)) {
        LOG_ERROR_FOR("DataPack::Pack", QString("Wrong XML: (%1:%2) %3").arg(line).arg(col).arg(error));
        return;
    }
    QDomElement root = doc.firstChildElement(::TAG_ROOT);
    QDomElement descr = root.firstChildElement(::TAG_PACKDESCRIPTION);
    QDomElement dep = root.firstChildElement(::TAG_PACKDEPENDENCIES);
    m_descr.fromDomElement(descr);
    m_depends.fromDomElement(dep);
}
