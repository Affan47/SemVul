mpz_pow2abs_p (mpz_srcptr z)
{
  mp_size_t  size, i;
  mp_srcptr  ptr;

  size = SIZ (z);
  if (size == 0)
    return 0;
  size = ABS (size);

  ptr = PTR (z);
  for (i = 0; i < size-1; i++)
    if (ptr[i] != 0)
      return 0;

  return POW2_P (ptr[i]);
}
