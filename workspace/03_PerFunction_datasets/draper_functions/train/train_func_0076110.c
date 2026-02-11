hasAttributeNS( const DOMString &namespaceURI,
                                  const DOMString &localName ) const
{
    NamespaceName namespacename = NamespaceName::fromString(namespaceURI);
    LocalName localname = LocalName::fromString(localName, m_htmlCompat ? IDS_NormalizeLower : IDS_CaseSensitive);
    NodeImpl::Id id = makeId(namespacename.id(), localname.id());
    if (!id) return false;
    if (!namedAttrMap) return false;
    return namedAttrMap->getValue(id, emptyPrefixName, true) != 0;
}
