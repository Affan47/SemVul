construct_djvutxt(ParsingByteStream &pbs)
{
  GP<DjVuTXT> txt(DjVuTXT::create());
  int c = pbs.get_spaces(true);
  if (c == EOF)
    return 0;
  pbs.unget(c);
  construct_djvutxt_sub(pbs, txt, txt->page_zone, DjVuTXT::PAGE, true);
  if (pbs.get_spaces(true) != EOF)
    verror("Syntax error in txt data: garbage after data");
  txt->normalize_text();
  if (! txt->textUTF8)
    return 0;
  return txt;
}
