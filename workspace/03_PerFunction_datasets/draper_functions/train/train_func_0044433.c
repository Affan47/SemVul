parse()
{
    std::size_t nDone = 0;
    std::size_t nLen = 0;
    char aBuf[BUFSIZ] = { 0 };

    if( NULL == pKMLFile_ )
    {
        sError_ = "No file given";
        return;
    }

    if(poTrunk_ != NULL) {
        delete poTrunk_;
        poTrunk_ = NULL;
    }

    if(poCurrent_ != NULL)
    {
        delete poCurrent_;
        poCurrent_ = NULL;
    }

    XML_Parser oParser = OGRCreateExpatXMLParser();
    XML_SetUserData(oParser, this);
    XML_SetElementHandler(oParser, startElement, endElement);
    XML_SetCharacterDataHandler(oParser, dataHandler);
    oCurrentParser = oParser;
    nWithoutEventCounter = 0;

    do
    {
        nDataHandlerCounter = 0;
        nLen = (int)VSIFReadL( aBuf, 1, sizeof(aBuf), pKMLFile_ );
        nDone = VSIFEofL(pKMLFile_);
        if (XML_Parse(oParser, aBuf, nLen, nDone) == XML_STATUS_ERROR)
        {
            CPLError(CE_Failure, CPLE_AppDefined,
                        "XML parsing of KML file failed : %s at line %d, column %d",
                        XML_ErrorString(XML_GetErrorCode(oParser)),
                        (int)XML_GetCurrentLineNumber(oParser),
                        (int)XML_GetCurrentColumnNumber(oParser));
            XML_ParserFree(oParser);
            VSIRewindL(pKMLFile_);
            return;
        }
        nWithoutEventCounter ++;
    } while (!nDone && nLen > 0 && nWithoutEventCounter < 10);

    XML_ParserFree(oParser);
    VSIRewindL(pKMLFile_);
    poCurrent_ = NULL;

    if (nWithoutEventCounter == 10)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Too much data inside one element. File probably corrupted");
    }
}
