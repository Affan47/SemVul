totitle_func(const struct unicode_info *u,
			  const char *cp, int *ip)
{
  unicode_char *uc = (*u->c2u)(u, cp, ip);
  char *s;

  if (!uc)
    return (NULL);


  s = (*u->u2c)(u, uc, NULL);
  free(uc);
  return (s);
}
