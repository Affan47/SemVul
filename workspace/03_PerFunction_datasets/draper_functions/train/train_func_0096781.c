digit_value_in_base (int c, int base)
{
  int digit;

  MPFR_ASSERTD (base > 0 && base <= MPFR_MAX_BASE);

  if (c >= '0' && c <= '9')
    digit = c - '0';
  else if (c >= 'a' && c <= 'z')
    digit = (base >= 37) ? c - 'a' + 36 : c - 'a' + 10;
  else if (c >= 'A' && c <= 'Z')
    digit = c - 'A' + 10;
  else
    return -1;

  return MPFR_LIKELY (digit < base) ? digit : -1;
}
