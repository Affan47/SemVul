unicodeToUpper(Unicode c) {
  int i;

  if (c > 0xffff) {
    return c;
  }
  i = (c >> 8) & 0xff;
  if (caseTable[i]) {
    return caseTable[i]->codes[c & 0xff];
  }
  return c;
}
