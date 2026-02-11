startPrefixMapping(const XMLString& prefix, const XMLString& namespaceURI)
{
	if (prefix != NamespaceSupport::XML_NAMESPACE_PREFIX)
	{
		if (!_nsContextPushed)
		{
			_namespaces.pushContext();
			_nsContextPushed = true;
		}
		_namespaces.declarePrefix(prefix, namespaceURI);
	}
}
