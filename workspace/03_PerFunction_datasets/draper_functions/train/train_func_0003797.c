s48_bignum_equal_p(bignum_type x, bignum_type y)
{
  return
    ((BIGNUM_ZERO_P (x))
     ? (BIGNUM_ZERO_P (y))
     : ((! (BIGNUM_ZERO_P (y)))
	&& ((BIGNUM_NEGATIVE_P (x))
	    ? (BIGNUM_NEGATIVE_P (y))
	    : (! (BIGNUM_NEGATIVE_P (y))))
	&& (bignum_equal_p_unsigned (x, y))));
}
