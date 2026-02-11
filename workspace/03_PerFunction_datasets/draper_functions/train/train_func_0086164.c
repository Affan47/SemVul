bignum_shorten_length(bignum_type bignum, bignum_length_type length)
{
  bignum_length_type current_length = (BIGNUM_LENGTH (bignum));
  BIGNUM_ASSERT ((length >= 0) || (length <= current_length));
  if (length < current_length)
    {
      BIGNUM_REDUCE_LENGTH (bignum, length);
      BIGNUM_SET_NEGATIVE_P (bignum, (length != 0) && (BIGNUM_NEGATIVE_P (bignum)));
    }
  return (bignum);
}
