construct_outline(ParsingByteStream &pbs)
{
  GP<DjVmNav> nav(DjVmNav::create());
  int c = pbs.get_spaces(true);
  int count = 0;
  if (c == EOF)
    return 0;
  if (c!='(')
    verror("Syntax error in outline data: expecting '(bookmarks'");
  if (pbs.get_token()!="bookmarks")
    verror("Syntax error in outline data: expecting '(bookmarks'");
  while ((c = pbs.get_spaces(true)) == '(')
    construct_outline_sub(pbs, nav, count);
  if (c != ')')
    verror("Syntax error in outline: expecting parenthesis,\n\tnear '%s'.",
           pbs.get_error_context(c) );
  if (pbs.get_spaces(true) != EOF)
    verror("Syntax error in outline: garbage after last ')',\n\tnear '%s'",
           pbs.get_error_context(c) );
  if (nav->getBookMarkCount() < 1)
    return 0;
  if (!nav->isValidBookmark())
    verror("Invalid outline data!");
  return nav;
}
