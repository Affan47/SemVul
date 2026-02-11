unparsedEntityDecl(const XMLString& name, const XMLString* publicId, const XMLString& systemId, const XMLString& notationName)
{
	DocumentType* pDoctype = _pDocument->getDoctype();
	if (pDoctype)
	{
		AutoPtr<Entity> pEntity = _pDocument->createEntity(name, publicId ? *publicId : EMPTY_STRING, systemId, notationName);
		pDoctype->appendChild(pEntity);
	}
}
