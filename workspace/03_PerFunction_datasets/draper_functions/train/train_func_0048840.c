sub_whole (NODE_T * p, int n, int width)
{
  char *s = stack_string (p, 8 + width);
  int len = 0;
  s[0] = NULL_CHAR;
  do {
    if (len < width) {
      (void) plusto (digchar (n % 10), s);
    }
    len++;
    n /= 10;
  } while (n != 0);
  if (len > width) {
    (void) error_chars (s, width);
  }
  return (s);
}
