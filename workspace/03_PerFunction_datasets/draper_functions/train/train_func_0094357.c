getS32BE(int pos, GBool *ok) {
  int x;

  if (pos < 0 || pos+3 >= len) {
    *ok = gFalse;
    return 0;
  }
  x = file[pos];
  x = (x << 8) + file[pos+1];
  x = (x << 8) + file[pos+2];
  x = (x << 8) + file[pos+3];
  if (x & 0x80000000) {
    x |= ~0xffffffff;
  }
  return x;
}
