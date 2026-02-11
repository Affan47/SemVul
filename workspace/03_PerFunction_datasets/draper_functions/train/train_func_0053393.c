getU16BE(int pos, int *val) {
  if (!fillBuf(pos, 2)) {
    return gFalse;
  }
  *val = ((buf[pos - bufPos] & 0xff) << 8) +
         (buf[pos - bufPos + 1] & 0xff);
  return gTrue;
}
