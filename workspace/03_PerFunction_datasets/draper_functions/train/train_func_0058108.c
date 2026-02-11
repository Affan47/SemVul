bgprintf(int size, char *fmt,...)
{
  static char fnc[] = "bgprintf";
  va_list ap;
  char *p = (char *) balloc(size + 1);

  va_start(ap, fmt);
  (void) vsprintf(p, fmt, ap);
  va_end(ap);

  if (strlen((DEV_STRARG) p) > size) {
    Abort("%t %s(): abort: size error: %d > %d\n", fnc, strlen((DEV_STRARG) p), size);
  }
  return p;
}
