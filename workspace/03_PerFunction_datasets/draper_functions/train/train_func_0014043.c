bignum_allocate(bignum_length_type length, int negative_p)
{
  BIGNUM_ASSERT ((length >= 0) || (length < BIGNUM_RADIX));
  {
    bignum_type result = (BIGNUM_ALLOCATE (length));
    BIGNUM_SET_HEADER (result, length, negative_p);
    return (result);
  }
}
