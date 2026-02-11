fl_utf_strncasecmp(const char *s1, const char *s2, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    int l1, l2;
    unsigned int u1, u2;

    if (*s1==0 && *s2==0) return 0;

    u1 = fl_utf8decode(s1, 0, &l1);
    u2 = fl_utf8decode(s2, 0, &l2);
    int res = XUtf8Tolower(u1) - XUtf8Tolower(u2);
    if (res) return res;
    s1 += l1;
    s2 += l2;
  }
  return 0;
}
