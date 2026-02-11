markup(XML_Parser parser, const XML_Char *s, int len)
{
  FILE *fp = XML_GetUserData(parser);
  for (; len > 0; --len, ++s)
    puttc(*s, fp);
}
