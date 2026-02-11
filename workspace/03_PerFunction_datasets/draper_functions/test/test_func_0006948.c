isprime(unsigned long n)
{
  unsigned int r;

  if (n % 2 == 0)
    return (n == 2);
  if (n % 3 == 0)
    return (n == 3);
  if (n % 5 == 0)
    return (n == 5);

  if (n / 30 >= sizeof (primemap))
    abort();

  r = n % 30;
  r = (r * 16 + r) / 64;

  return ((primemap[n / 30] & (1 << r)) != 0);
}
