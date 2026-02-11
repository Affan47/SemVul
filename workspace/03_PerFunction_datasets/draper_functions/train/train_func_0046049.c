parseCharInputStream(XMLCharInputStream& istr)
{
	std::streamsize n = readChars(istr, reinterpret_cast<XMLChar*>(_pBuffer), PARSE_BUFFER_SIZE/sizeof(XMLChar));
	while (n > 0)
	{
		if (!XML_Parse(_parser, _pBuffer, static_cast<int>(n*sizeof(XMLChar)), 0))
			handleError(XML_GetErrorCode(_parser));
		if (istr.good())
			n = readChars(istr, reinterpret_cast<XMLChar*>(_pBuffer), PARSE_BUFFER_SIZE/sizeof(XMLChar));
		else
			n = 0;
	}
	if (!XML_Parse(_parser, _pBuffer, 0, 1))
		handleError(XML_GetErrorCode(_parser));
}
