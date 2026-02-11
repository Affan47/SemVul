removeNamedItemNS(const XMLString& namespaceURI, const XMLString& localName)
{
	Attr* pAttr = _pElement->getAttributeNodeNS(namespaceURI, localName);
	if (pAttr)
		return _pElement->removeAttributeNode(pAttr);
	else
		return 0;
}
