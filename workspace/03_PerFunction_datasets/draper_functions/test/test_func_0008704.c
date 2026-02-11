bignum_destructive_add(bignum_type bignum, bignum_digit_type n)
{
  bignum_digit_type * scan = (BIGNUM_START_PTR (bignum));
  bignum_digit_type digit;
  digit = ((*scan) + n);
  if (digit < BIGNUM_RADIX)
    {
      (*scan) = digit;
      return;
    }
  (*scan++) = (digit - BIGNUM_RADIX);
  while (1)
    {
      digit = ((*scan) + 1);
      if (digit < BIGNUM_RADIX)
        {
          (*scan) = digit;
          return;
        }
      (*scan++) = (digit - BIGNUM_RADIX);
    }
}
