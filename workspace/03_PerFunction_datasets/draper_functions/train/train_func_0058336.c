is_po2(size_t i)
{
  if (i == 0)
    return 0;
  return (((i & (i - 1)) == 0) ? 1 : 0);
}
