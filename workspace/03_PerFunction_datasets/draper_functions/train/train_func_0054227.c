mkutf(unsigned long x)
{
  memset(ubuf, 0, 4);
  if(x < 128) ubuf[0] = x;
  else if(x < 0x800) {
     ubuf[0] = (0xc0 | ((x >> 6) & 0x1f));
     ubuf[1] = (0x80 | (x & 0x3f));
  }
  else {
     ubuf[0] = (0xe0 | ((x >> 12) & 0x0f));
     ubuf[1] = (0x80 | ((x >> 6) & 0x3f));
     ubuf[2] = (0x80 | (x & 0x3f));
  }
  return ubuf;
}
