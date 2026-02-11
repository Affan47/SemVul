lang_compare_first_component (const void *pa,
			      const void *pb)
{
  const char *a = pa, *b = pb;
  unsigned int da, db;
  const char *p;

  p = strstr (a, "-");
  da = p ? (unsigned int) (p - a) : strlen (a);

  p = strstr (b, "-");
  db = p ? (unsigned int) (p - b) : strlen (b);

  return strncmp (a, b, MAX (da, db));
}
