getElementByIdNS(const XMLString& elementId, const XMLString& idAttributeURI, const XMLString& idAttributeLocalName) const
{
	Element* pElem = documentElement();
	if (pElem) pElem = pElem->getElementByIdNS(elementId, idAttributeURI, idAttributeLocalName);
	return pElem;
}
