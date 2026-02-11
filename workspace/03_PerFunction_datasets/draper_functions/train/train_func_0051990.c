bignum_divide_unsigned_large_denominator(bignum_type numerator,
                                         bignum_type denominator,
                                         bignum_type * quotient,
                                         bignum_type * remainder,
                                         int q_negative_p,
                                         int r_negative_p)
{
  bignum_length_type length_n = ((BIGNUM_LENGTH (numerator)) + 1);
  bignum_length_type length_d = (BIGNUM_LENGTH (denominator));

  REGISTER_BIGNUM(numerator);
  REGISTER_BIGNUM(denominator);

  bignum_type q =
    ((quotient != ((bignum_type *) 0))
     ? (allot_bignum ((length_n - length_d), q_negative_p))
     : BIGNUM_OUT_OF_BAND);

  REGISTER_BIGNUM(q);
  bignum_type u = (allot_bignum (length_n, r_negative_p));
  UNREGISTER_BIGNUM(q);

  UNREGISTER_BIGNUM(denominator);
  UNREGISTER_BIGNUM(numerator);

  int shift = 0;
  BIGNUM_ASSERT (length_d > 1);
  {
    bignum_digit_type v1 = (BIGNUM_REF ((denominator), (length_d - 1)));
    while (v1 < (BIGNUM_RADIX / 2))
      {
        v1 <<= 1;
        shift += 1;
      }
  }
  if (shift == 0)
    {
      bignum_destructive_copy (numerator, u);
      (BIGNUM_REF (u, (length_n - 1))) = 0;
      bignum_divide_unsigned_normalized (u, denominator, q);
    }
  else
    {
      REGISTER_BIGNUM(numerator);
      REGISTER_BIGNUM(denominator);
      REGISTER_BIGNUM(u);
      REGISTER_BIGNUM(q);
      bignum_type v = (allot_bignum (length_d, 0));
      UNREGISTER_BIGNUM(q);
      UNREGISTER_BIGNUM(u);
      UNREGISTER_BIGNUM(denominator);
      UNREGISTER_BIGNUM(numerator);

      bignum_destructive_normalization (numerator, u, shift);
      bignum_destructive_normalization (denominator, v, shift);
      bignum_divide_unsigned_normalized (u, v, q);
      if (remainder != ((bignum_type *) 0))
        bignum_destructive_unnormalization (u, shift);
    }

  REGISTER_BIGNUM(u);
  if(q)
    q = bignum_trim (q);
  UNREGISTER_BIGNUM(u);

  REGISTER_BIGNUM(q);
  u = bignum_trim (u);
  UNREGISTER_BIGNUM(q);

  if (quotient != ((bignum_type *) 0))
    (*quotient) = q;

  if (remainder != ((bignum_type *) 0))
    (*remainder) = u;

  return;
}
