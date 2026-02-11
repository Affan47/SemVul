fromInt(int x) {
  char buf[24];
  char *p;
  int len;
  formatInt(x, buf, sizeof(buf), gFalse, 0, 10, &p, &len);
  return new GooString(p, len);
}
