unknownEncoding(void *userData,
		    const XML_Char *name,
		    XML_Encoding *info)
{
  int cp;
  static const XML_Char prefixL[] = T("windows-");
  static const XML_Char prefixU[] = T("WINDOWS-");
  int i;

  for (i = 0; prefixU[i]; i++)
    if (name[i] != prefixU[i] && name[i] != prefixL[i])
      return 0;

  cp = 0;
  for (; name[i]; i++) {
    static const XML_Char digits[] = T("0123456789");
    const XML_Char *s = tcschr(digits, name[i]);
    if (!s)
      return 0;
    cp *= 10;
    cp += s - digits;
    if (cp >= 0x10000)
      return 0;
  }
  if (!codepageMap(cp, info->map))
    return 0;
  info->convert = unknownEncodingConvert;


  info->release = free;
  info->data = malloc(sizeof(int));
  if (!info->data)
    return 0;
  *(int *)info->data = cp;
  return 1;
}
