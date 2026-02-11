soapType(QDomNode node) const
{
    if (node.isNull() || !node.isElement())
	return QtSmartPtr<QtSoapType>();

    QDomElement elem = node.toElement();

    QDomAttr attr = elem.attributeNode("type");
    QtSoapTypeConstructorBase *constructor = 0;
    if (!attr.isNull()) {
        QHash<QString, QtSoapTypeConstructorBase *>::ConstIterator it;
	it = typeHandlers.find(localName(attr.value().toLower()));
        if (it != typeHandlers.end())
            constructor = *it;
    }

    if (attr.isNull() || !constructor) {
        QHash<QString, QtSoapTypeConstructorBase *>::ConstIterator it;
	if (node.firstChild().isElement()) {
            if (localName(node.nodeName().toLower()) == "array") {
                it = typeHandlers.find("array");
            } else
                it = typeHandlers.find("struct");
        } else
	    it = typeHandlers.find("string");
        if (it != typeHandlers.end())
            constructor = *it;
    }

    if (!constructor) {
	return QtSmartPtr<QtSoapType>();
    }

    QtSoapType *type = constructor->createObject(node);

    if (!type)
	errorStr = constructor->errorString();

    return QtSmartPtr<QtSoapType>(type);
}
