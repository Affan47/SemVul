SetupParserExpat()
{

    if( oParser != NULL )
        CleanupParser();

    oParser = OGRCreateExpatXMLParser();
    m_poGMLHandler = new GMLExpatHandler( this, oParser );

    XML_SetElementHandler(oParser, GMLExpatHandler::startElementCbk, GMLExpatHandler::endElementCbk);
    XML_SetCharacterDataHandler(oParser, GMLExpatHandler::dataHandlerCbk);
    XML_SetUserData(oParser, m_poGMLHandler);

    if (pabyBuf == NULL)
        pabyBuf = (char*)VSIMalloc(PARSER_BUF_SIZE);
    if (pabyBuf == NULL)
        return FALSE;

    return TRUE;
}
