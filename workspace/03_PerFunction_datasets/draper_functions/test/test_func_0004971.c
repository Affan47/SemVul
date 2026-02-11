metaStartNamespaceDecl(void *userData,
                       const XML_Char *prefix,
                       const XML_Char *uri)
{
  XML_Parser parser = (XML_Parser) userData;
  FILE *fp = (FILE *)XML_GetUserData(parser);
  fputts(T("<startns"), fp);
  if (prefix)
    ftprintf(fp, T(" prefix=\"%s\""), prefix);
  if (uri) {
    fputts(T(" ns=\""), fp);
    characterData(fp, uri, (int)tcslen(uri));
    fputts(T("\"/>\n"), fp);
  }
  else
    fputts(T("/>\n"), fp);
}
