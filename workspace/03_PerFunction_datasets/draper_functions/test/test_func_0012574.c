isSpace(int c) {
  return c >= 0 && c <= 0xff && specialChars[c] == 1;
}
