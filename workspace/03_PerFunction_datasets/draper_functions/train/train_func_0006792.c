notationDecl(const XMLString& name, const XMLString* publicId, const XMLString* systemId)
{
	DocumentType* pDoctype = _pDocument->getDoctype();
	if (pDoctype)
	{
		AutoPtr<Notation> pNotation = _pDocument->createNotation(name, (publicId ? *publicId : EMPTY_STRING), (systemId ? *systemId : EMPTY_STRING));
		pDoctype->appendChild(pNotation);
	}
}
