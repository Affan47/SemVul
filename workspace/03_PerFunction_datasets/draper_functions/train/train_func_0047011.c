my_decimal_trim(ulong *precision, uint *scale)
{
  if (!(*precision) && !(*scale))
  {
    *precision= 10;
    *scale= 0;
    return;
  }
}
