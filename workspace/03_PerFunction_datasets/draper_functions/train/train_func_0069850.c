addElement(QDomDocument& doc, QDomElement& parent,
                                         const QString& tag, const QString& value)
    {
        QDomElement n = doc.createElement(tag);
        n.appendChild(doc.createTextNode(value));
        parent.appendChild(n);

        return n;
    }
}
