bankno (char *s, int n) {

  long res = 0;
  int c;
  while(n-- > 0) {
    c = (*s++);
    if (islower(c))
      c -= 'a';
    else if (isupper(c))
      c -= 'A';
    else
      c -= '1';
    res = res * 8 + c;
  }
  return res;
}
