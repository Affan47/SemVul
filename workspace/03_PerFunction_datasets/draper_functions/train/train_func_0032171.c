check_is_sorted (unsigned long n, mpfr_srcptr *perm)
{
  unsigned long i;

  for (i = 0; i < n - 1; i++)
    if (MPFR_GET_EXP(perm[i]) < MPFR_GET_EXP(perm[i+1]))
      return 0;
  return 1;
}
