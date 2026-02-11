metaStartNamespaceDecl(XML_Parser parser,
			    const XML_Char *prefix,
			    const XML_Char *uri)
{
  FILE *fp = XML_GetUserData(parser);
  fputts(T("<startns"), fp);
  if (prefix)
    ftprintf(fp, T(" prefix=\"%s\""), prefix);
  if (uri) {
    fputts(T(" ns=\""), fp);
    characterData(fp, uri, tcslen(uri));
    fputts(T("\"/>\n"), fp);
  }
  else
    fputts(T("/>\n"), fp);
}
