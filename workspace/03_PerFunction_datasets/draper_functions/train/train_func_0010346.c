toupper_func(const struct unicode_info *u,
			  const char *cp, int *ip)
{
  unicode_char *uc = c2u(u, cp, ip);
  char *s;
  size_t i;

  if (!uc)
    return (NULL);

  for (i=0; uc[i] && i<10000; i++) {
    if ((unicode_char)'a' <= uc[i] && uc[i] <= (unicode_char)'z')
      uc[i] = uc[i] - ((unicode_char)'a' - (unicode_char)'A');
  }

  s = u2c(u, uc, NULL);
  free(uc);
  return (s);
}
