MaybeParsePerlCCEscape(StringPiece* s, Regexp::ParseFlags parse_flags) {
  if (!(parse_flags & Regexp::PerlClasses))
    return NULL;
  if (s->size() < 2 || (*s)[0] != '\\')
    return NULL;


  StringPiece name(s->begin(), 2);
  const UGroup *g = LookupPerlGroup(name);
  if (g == NULL)
    return NULL;
  s->remove_prefix(name.size());
  return g;
}
