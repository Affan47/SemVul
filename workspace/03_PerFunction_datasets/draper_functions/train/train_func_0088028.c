getTrailer()
{
  getToken();
  if (iTok.iType != PdfToken::EDictBg)
    return 0;
  getToken();
  return makeDict();
}
