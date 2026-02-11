hexDigitValue(unsigned int c)
{
  unsigned int r;

  r = c - '0';
  if (r <= 9)
    return r;

  r = c - 'A';
  if (r <= 5)
    return r + 10;

  r = c - 'a';
  if (r <= 5)
    return r + 10;

  return -1U;
}
