luaV_strcomp (const TString *ls, const TString *rs) {
  const char *l = ls->str;
  size_t ll = ls->len;
  const char *r = rs->str;
  size_t lr = rs->len;
  for (;;) {
    int temp = strcoll(l, r);
    if (temp != 0) return temp;
    else {
      size_t len = strlen(l);
      if (len == ll)
        return (len == lr) ? 0 : -1;
      else if (len == lr)
        return 1;

      len++;
      l += len; ll -= len; r += len; lr -= len;
    }
  }
}
