setAttributeNS( const DOMString &namespaceURI, const DOMString &qualifiedName,
				const DOMString &value, int &exceptioncode )
{

    if (isReadOnly()) {
        exceptioncode = DOMException::NO_MODIFICATION_ALLOWED_ERR;
        return;
    }
    int colonPos;
    if (!DOM::checkQualifiedName(qualifiedName, namespaceURI, &colonPos,
                                 false, false,
                                 &exceptioncode))
        return;
    LocalName localname;
    PrefixName prefixname;
    splitPrefixLocalName(qualifiedName, prefixname, localname, m_htmlCompat, colonPos);
    NamespaceName namespacename = NamespaceName::fromString(namespaceURI);
    attributes()->setValue(makeId(namespacename.id(), localname.id()), value.implementation(), prefixname, true );
}
