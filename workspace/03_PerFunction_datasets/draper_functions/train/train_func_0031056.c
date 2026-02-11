pkg_category(const char *str)
{
  int rc;
  if (0 < (rc = pkg_match(str)))
  {
    const char *s = NULL;

    if (0 > pcre_get_named_substring(atom_re, str, atom_sub, rc, CAT, &s))
      return NULL;

    char *tmp = pool_add(strdup(s));

    pcre_free_substring(s);

    return tmp;
  }
  return NULL;
}
