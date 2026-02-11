grep_in_string (char *pat, char *str, int *start, int *end)
{
#if defined HAVE_REGEX_H
  int rc, nmatch, k, max_k, widest;
  regex_t compiled;
  regmatch_t *matches;
  rc = regcomp (&compiled, pat, REG_NEWLINE | REG_EXTENDED);
  if (rc != 0) {
    regfree (&compiled);
    return (rc);
  }
  nmatch = (int) (RE_NSUB (&compiled));
  if (nmatch == 0) {
    nmatch = 1;
  }
  matches = malloc ((size_t) (nmatch * ALIGNED_SIZE_OF (regmatch_t)));
  if (nmatch > 0 && matches == NO_REGMATCH) {
    regfree (&compiled);
    return (2);
  }
  rc = regexec (&compiled, str, (size_t) nmatch, matches, 0);
  if (rc != 0) {
    regfree (&compiled);
    return (rc);
  }

  widest = 0;
  max_k = 0;
  for (k = 0; k < nmatch; k++) {
    int dif = (int) RM_EO (&matches[k]) - (int) RM_SO (&matches[k]);
    if (dif > widest) {
      widest = dif;
      max_k = k;
    }
  }
  if (start != NO_INT) {
    (*start) = (int) RM_SO (&matches[max_k]);
  }
  if (end != NO_INT) {
    (*end) = (int) RM_EO (&matches[max_k]);
  }
  free (matches);
  return (0);
#else
  (void) start;
  (void) end;
  if (strstr (str, pat) != NO_TEXT) {
    return (0);
  } else {
    return (1);
  }
#endif
}
