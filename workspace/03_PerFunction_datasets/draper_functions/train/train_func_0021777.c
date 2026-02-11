lj_carith_divi64(int64_t a, int64_t b)
{
  if (b == 0 || (a == (int64_t)U64x(80000000,00000000) && b == -1))
    return U64x(80000000,00000000);
  return a / b;
}
