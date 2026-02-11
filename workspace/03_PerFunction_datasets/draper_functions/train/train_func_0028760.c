power10ed(unsigned char val) {
  int exp = val%15;
  int n = 1;
  while (--exp) n *= 10;
  return n * (val >> 4);
}
