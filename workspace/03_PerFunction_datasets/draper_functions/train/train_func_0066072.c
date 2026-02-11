dns_random(unsigned int n)
{
  if (!n) return 0;

  if (!outleft) {
    if (!++in[0]) if (!++in[1]) if (!++in[2]) ++in[3];
    surf();
    outleft = 8;
  }

  return out[--outleft] % n;
}
