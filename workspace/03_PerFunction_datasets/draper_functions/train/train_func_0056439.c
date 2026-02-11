cd(QDomNode node, const QString &name, bool create)
{
    QDomNode subnode = node.namedItem(name);
    if (create && subnode.isNull())
    {
        subnode = node.ownerDocument().createElement(name);
        node.appendChild(subnode);
    }
    return subnode;
}
