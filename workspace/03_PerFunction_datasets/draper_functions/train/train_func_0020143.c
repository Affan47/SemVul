Read()
{
  std::ifstream is( Filename.c_str(), std::ios::binary );

  char buf[BUFSIZ];
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;

  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterDataHandler);
  int ret = 0;
  do {
    is.read(buf, sizeof(buf));
	  std::streamsize len = is.gcount();
    done = (unsigned int)len < sizeof(buf);
    if (XML_Parse(parser, buf, (int)len, done) == XML_STATUS_ERROR) {
      fprintf(stderr,
        "%s at line %" XML_FMT_INT_MOD "u\n",
        XML_ErrorString(XML_GetErrorCode(parser)),
        XML_GetCurrentLineNumber(parser));
      ret = 1;
      done = 1;
    }
  } while (!done);
  XML_ParserFree(parser);
  is.close();
  return ret;
}
