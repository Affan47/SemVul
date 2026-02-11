airParseStrC(char *out, const char *_s, const char *ct, unsigned int n, ...) {
  unsigned int i;
  char *tmp, *s, *last;


  if (!(out && _s && ct))
    return 0;


  s = airStrdup(_s);


  for (i=0; i<n; i++) {
    tmp = airStrtok(i ? NULL : s, ct, &last);
    if (!tmp) {
      free(s);
      return i;
    }
    out[i] = tmp[0];
  }
  free(s);
  return n;
}
