gt_string_matching_bmh(const char *s, unsigned long n,
                            const char *p, unsigned long m,
                            GtProcessMatch process_match, void *data)
{
  unsigned long i, j, pos, d[UCHAR_MAX];
  gt_assert(s && p);
  if (m > n || !m || !n)
    return;

  for (i = 0; i < UCHAR_MAX; i++)
    d[i] = m;
  for (j = 0; j < m-1; j++)
    d[(unsigned) p[j]] = m-(j+1);

  pos = 0;
  while (pos <= n-m) {
    j = m;
    while (j > 0 && s[pos+j-1] == p[j-1])
      j--;
    if (j == 0 && process_match) {
      if (process_match(pos, data))
        return;
    }
    pos += d[(unsigned) s[pos+m-1]];
  }
}
