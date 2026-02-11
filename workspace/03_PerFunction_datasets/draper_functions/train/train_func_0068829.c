getProperty(const XMLString& propertyId) const
{
	if (propertyId == XMLReader::PROPERTY_DECLARATION_HANDLER)
		return _engine.getDeclHandler();
	else if (propertyId == XMLReader::PROPERTY_LEXICAL_HANDLER)
		return _engine.getLexicalHandler();
	else throw SAXNotSupportedException(fromXMLString(propertyId));
}
