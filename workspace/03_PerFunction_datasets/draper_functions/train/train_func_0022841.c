nav_read(void)
{
  int len;
  char buf[MY_CBUF];

  while ((len = gbfread(buf, 1, sizeof(buf), fin))) {
    if (!XML_Parse(psr, buf, len, gbfeof(fin))) {
      fatal(MYNAME ":Parse error at %d: %s\n",
            (int) XML_GetCurrentLineNumber(psr),
            XML_ErrorString(XML_GetErrorCode(psr)));
    }
  }

  XML_ParserFree(psr);
}
