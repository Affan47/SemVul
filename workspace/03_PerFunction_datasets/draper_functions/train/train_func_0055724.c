Parse( const std::string& xml, ModuleDescription& description)
{

  if (strncmp(xml.c_str(),"<?xml ", 6) != 0)
    {
    std::string required("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
    std::cerr << "ModuleDescriptionParser: first line must be " << std::endl;
    std::cerr << required << std::endl;
    return 1;
    }

  ParserState parserState;
  parserState.CurrentDescription = description;

  XML_Parser parser = XML_ParserCreate(NULL);
  int done;

  parserState.Parser = parser;
  parserState.CurrentParameter = 0;
  parserState.CurrentGroup = 0;

  XML_SetUserData(parser, static_cast<void *>(&parserState));
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, charData);


  done = true;
  int status = 0;
  if (XML_Parse(parser, xml.c_str(), static_cast< int >(xml.size()), done) == 0)
    {
    std::cerr << XML_ErrorString(XML_GetErrorCode(parser))
              << " at line "
              << XML_GetCurrentLineNumber(parser)
              << std::endl;
    status = 1;
    }
  else
    {
    if (parserState.Error)
      {
      std::cerr << parserState.ErrorDescription
                << " at line "
                <<  parserState.ErrorLine
                << " while parsing "
                << xml
                << std::endl;
      status = 1;
      }
    }

  XML_ParserFree(parser);

  description = parserState.CurrentDescription;
  return status;
}
