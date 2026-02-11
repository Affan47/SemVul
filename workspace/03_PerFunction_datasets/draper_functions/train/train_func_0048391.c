str_case_startb(const str* a, const char* b, unsigned len)
{
  const char* aptr;
  if (len > a->len) return 0;
  for (aptr = a->s; len > 0; --len) {
    char bc = *b++;
    char ac = *aptr++;
    if (isupper(bc)) bc = tolower(bc);
    if (isupper(ac)) ac = tolower(ac);
    if (ac != bc) return 0;
  }
  return 1;
}
