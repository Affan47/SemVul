handleNotation(const Notation* pNotation) const
{
	if (_pDTDHandler) _pDTDHandler->notationDecl(pNotation->nodeName(), &pNotation->publicId(), &pNotation->systemId());
}
