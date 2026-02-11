add_keyword_error(StringAccum &sa, int err, const String &arg,
			      const char *argname, int argno)
{
  if (err >= 0)
    return;
  if (sa.length())
    sa << ", ";
  if (err == kwNoKeyword)
    sa << '<' << argname << ' ' << (argno + 1) << '>';
  else {
    String keyword, rest;
    (void) cp_keyword(arg, &keyword, &rest);
    sa << keyword;
    if (err == kwDupKeyword)
      sa << " (duplicate keyword)";
  }
}
