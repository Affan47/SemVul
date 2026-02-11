createStringEntry(QDomDocument &doc, const QString &tagName, const QString &str)
{
    QDomElement el = doc.createElement(tagName);

    el.appendChild(doc.createTextNode(str));
    return el;
}
