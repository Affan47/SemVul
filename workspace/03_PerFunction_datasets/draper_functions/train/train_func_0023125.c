kdt_size (const Kdt * kdt, long len)
{
  long len1 = 1;
  while (len > kdt->h.np) {
    len /= 2; len1 *= 2;
  }
  return (len1 - 1)*sizeof (Node) + len1*sizeof (KdtPoint)*kdt->h.np;
}
