readHeader(const char *model)
{
	handler=dbgnew class ParserHandler(this,model);
	parser=XMLReaderFactory::createXMLReader();

    parser->setFeature(XMLUni::fgSAX2CoreValidation, false);

	parser->setProperty(XMLUni::fgXercesScannerName,(void *)XMLUni::fgWFXMLScanner);
    parser->setContentHandler(handler);
    parser->setEntityResolver(handler);
    parser->setErrorHandler(handler);
	return readLoop(filename);
}
