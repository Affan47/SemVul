log(unsigned n)
{
  unsigned r = 0;
  for (unsigned i = 1; i < n; ++r) i <<= 1;
  return r;
}
