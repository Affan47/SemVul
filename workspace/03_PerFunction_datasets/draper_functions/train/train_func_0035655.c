metaEndNamespaceDecl(void *userData, const XML_Char *prefix)
{
  XML_Parser parser = (XML_Parser) userData;
  FILE *fp = (FILE *)XML_GetUserData(parser);
  if (!prefix)
    fputts(T("<endns/>\n"), fp);
  else
    ftprintf(fp, T("<endns prefix=\"%s\"/>\n"), prefix);
}
