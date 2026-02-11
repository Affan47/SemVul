endElement(const XMLChar* name, ContentHandler* pContentHandler)
{
	poco_assert_dbg (name && pContentHandler);

	splitName(name, _uri, _local, _qname);
	if (!_qname.empty()) _qname += ':';
	_qname.append(_local);
	pContentHandler->endElement(_uri, _local, _qname);
}
