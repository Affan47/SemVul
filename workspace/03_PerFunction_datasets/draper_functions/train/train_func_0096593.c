bit_count (unsigned long value)
{
  unsigned long count = 0;

  while (value)
    {
      count++;
      value &= value - 1;
    }

  return count;
}
