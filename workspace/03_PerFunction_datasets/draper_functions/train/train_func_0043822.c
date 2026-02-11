parse(void)
{
  XML_Parser Parser = XML_ParserCreate(0);

  XML_SetElementHandler(Parser,
                        &itkXMLParserStartElement,
                        &itkXMLParserEndElement);

  XML_SetCharacterDataHandler(Parser,
                              &itkXMLParserCharacterDataHandler);
  XML_SetUserData(Parser, this);

  std::ifstream inputstream;

  inputstream.open(m_Filename.c_str(), std::ios::binary | std::ios::in);
  if ( inputstream.fail() )
    {
    ExceptionObject exception(__FILE__, __LINE__);
    std::string     message = "Can't open ";
    message += m_Filename;
    message += '\n';
    exception.SetDescription( message.c_str() );
    throw exception;
    }


  std::streamsize filesize =
    itksys::SystemTools::FileLength( m_Filename.c_str() );

  char *buffer = new char[filesize];

  inputstream.read(buffer, filesize);

  if ( static_cast< std::streamsize >( inputstream.gcount() ) != filesize )
    {
    ExceptionObject exception(__FILE__, __LINE__);
    exception.SetDescription("File Read Error");
    throw exception;
    }
  const bool result = static_cast<bool>(XML_Parse(Parser, buffer, inputstream.gcount(), false));
  delete[] buffer;
  if ( !result )
    {
    ExceptionObject exception(__FILE__, __LINE__);

    std::string message( XML_ErrorString( XML_GetErrorCode(Parser) ) );
    message += " ";
    message += m_Filename;
    message += '\n';
    exception.SetDescription( message.c_str() );
    throw exception;
    }
  XML_ParserFree(Parser);
  return;
}
