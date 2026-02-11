max_expand (MatchState *ms, const char *s,
                                 const char *p, const char *ep) {
  int i = 0;
  while ((s+i) < ms->src_end && singlematch(uchar(*(s+i)), p, ep))
    i++;

  while (i>=0) {
    const char *res = match(ms, (s+i), ep+1);
    if (res) return res;
    i--;
  }
  return NULL;
}
