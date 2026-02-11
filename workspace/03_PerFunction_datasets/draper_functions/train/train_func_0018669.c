min_value (unsigned int prec, bool uns)
{
  if (uns)
    return double_int_zero;
  return double_int_one.lshift (prec - 1, prec, false);
}
