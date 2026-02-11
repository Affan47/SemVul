readULong(Guint *x) {
  int c0, c1, c2, c3;

  if ((c0 = curStr->getChar()) == EOF ||
      (c1 = curStr->getChar()) == EOF ||
      (c2 = curStr->getChar()) == EOF ||
      (c3 = curStr->getChar()) == EOF) {
    return gFalse;
  }
  *x = (Guint)((c0 << 24) | (c1 << 16) | (c2 << 8) | c3);
  return gTrue;
}
