rand(void)
{
  if (! initialized)
  {
    time((time_t *)&next);
    initialized = 1;
  }
  next = next * 0x5deece66dLL + 11;
  return (int)((next >> 16) & 0x7fffffff);
}
