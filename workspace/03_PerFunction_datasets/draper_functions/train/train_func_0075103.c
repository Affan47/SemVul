bignum_unsigned_logbitp(int shift, bignum_type bignum)
{
  bignum_length_type len = (BIGNUM_LENGTH (bignum));
  int index = shift / BIGNUM_DIGIT_LENGTH;
  if (index >= len)
    return 0;
  bignum_digit_type digit = (BIGNUM_REF (bignum, index));
  int p = shift % BIGNUM_DIGIT_LENGTH;
  bignum_digit_type mask = ((F_FIXNUM)1) << p;
  return (digit & mask) ? 1 : 0;
}
