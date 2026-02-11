extractAtomText(const Syndication::ElementWrapper& parent, const QString& tagname)
{
    QString str;

    QDomElement el = parent.firstElementByTagNameNS(atom1Namespace(), tagname);

    bool isCDATA = el.firstChild().isCDATASection();

    QString type = el.attribute(QLatin1String("type"), QLatin1String("text"));

    if (type == QLatin1String("text"))
    {
        str = parent.extractElementTextNS(atom1Namespace(), tagname).trimmed();
        if (isCDATA)
            str = resolveEntities(str);

        str = escapeSpecialCharacters(str);
    }
    else if (type == QLatin1String("html"))
    {
        str = parent.extractElementTextNS(atom1Namespace(), tagname).trimmed();
    }
    else if (type == QLatin1String("xhtml"))
    {
        str = ElementWrapper::childNodesAsXML(el).trimmed();
    }

    return str;
}
