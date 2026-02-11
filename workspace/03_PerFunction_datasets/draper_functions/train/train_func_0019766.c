compile_people (void)
{
  a_read_data *p = 0;
  char *s = 0;
  const a_strpair *r = people_strings;
  s = xstrdup (r->i18n ? _(r->str) : r->str);
  while ((++r)->str)
    s = strappend (s, r->i18n ? _(r->str) : r->str);
  p = compile_reader_data (p, s);
  free (s);
  return p;
}
