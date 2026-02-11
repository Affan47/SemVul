sprintcbwt(const char *str, unsigned int *idxs, unsigned int len, char *out) {
  unsigned int i, d = 0xFFFFFFFF;
  char c = 0, u=3;
  for (i=0; i<=len; ++i) {
    if (idxs[i]) {
      c ^= getbase(str, idxs[i]-1)<<(2*u);
      if (u-- == 0) {
	out[i/4] = c;
	c = 0;
	u = 3;
      }
    }
    else {
      d = i;
      break;

    }
  }
  for (++i; i<=len; ++i) {
    c ^= getbase(str, idxs[i]-1)<<(2*u);
    if (u-- == 0) {
      out[(i-1)/4] = c;
      c = 0;
      u = 3;
    }
  }

  if (u != 3)
    out[((len+3)/4)-1] = c;
  return d;
}
