pos_mul_hwi (HOST_WIDE_INT x, HOST_WIDE_INT y)
{
  if (x != 0)
    gcc_checking_assert ((HOST_WIDE_INT_MAX) / x >= y);

  return x * y;
}
