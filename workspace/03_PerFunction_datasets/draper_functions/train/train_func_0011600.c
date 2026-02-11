intl_slist(int n, const char **s, bool *done)
{
  int i;

  if (!*done) {
    for(i=0; i<n; i++) {
      s[i] = Q_(s[i]);
    }

    *done = TRUE;
  }
}
