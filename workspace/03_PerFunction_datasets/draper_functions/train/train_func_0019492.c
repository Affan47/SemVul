s_mp_2expt(mp_int *a, mp_digit k)
{
  mp_err    res;
  mp_size   dig, bit;

  dig = k / DIGIT_BIT;
  bit = k % DIGIT_BIT;

  mp_zero(a);
  if((res = s_mp_pad(a, dig + 1)) != MP_OKAY)
    return res;

  DIGIT(a, dig) |= ((mp_digit)1 << bit);

  return MP_OKAY;

}
