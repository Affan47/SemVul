getChar()
{
  if (iIndex < iN)
    return iBuf[iIndex++];

  if (iEof)
    return EOF;

  int ch;
  do {
    ch = iSource.getChar();
  } while (ch == '\n' || ch == '\r' || ch == ' ');

  if (ch == '~' || ch == EOF) {
    iEof = true;
    iN = 0;
    return EOF;
  }

  iIndex = 1;
  iN = 4;

  if (ch == 'z') {
    iBuf[0] = iBuf[1] = iBuf[2] = iBuf[3] = 0;
    return iBuf[0];
  }

  int c[5];
  c[0] = ch;
  for (int k = 1; k < 5; ++k) {
    do {
      c[k] = iSource.getChar();
    } while (c[k] == '\n' || c[k] == '\r' || c[k] == ' ');
    if (c[k] == '~' || c[k] == EOF) {
      iN = k - 1;
      iEof = true;
      break;
    }
  }

  for (int k = iN + 1; k < 5; ++k)
    c[k] = 0x21 + 84;

  uint t = 0;
  for (int k = 0; k < 5; ++k)
    t = t * 85 + (c[k] - 0x21);

  for (int k = 3; k >= 0; --k) {
    iBuf[k] = char(t & 0xff);
    t >>= 8;
  }

  return iBuf[0];
}
