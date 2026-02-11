equals(const XMLString& qname, const XMLString& namespaceURI, const XMLString& localName) const
{
	return _namespaceURI == namespaceURI && _localName == localName && _qname == qname;
}
