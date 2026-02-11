nlz8(unsigned char x) {
  unsigned int b = 0;

  if (x & 0xf0) {
    x >>= 4;
  } else {
    b += 4;
  }

  if (x & 0x0c) {
    x >>= 2;
  } else {
    b += 2;
  }

  if (! (x & 0x02) ) {
    b++;
  }

  return b;
}
