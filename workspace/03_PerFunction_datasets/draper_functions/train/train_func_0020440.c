conv_cstr(const char *s, int from, int to)
{
  char *res;
  xstr *xs = anthy_cstr_to_xstr(s, from);
  if (!xs) {
    return NULL;
  }
  res = anthy_xstr_to_cstr(xs, to);
  anthy_free_xstr(xs);
  return res;
}
