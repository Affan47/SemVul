s48_extract_unsigned_integer(s48_value value)
{
  if (S48_FIXNUM_P(value))
    {
      long fixnum = S48_UNSAFE_EXTRACT_FIXNUM(value);
      if (fixnum < 0)
	s48_assertion_violation("s48_extract_unsigned_integer", "negative argument", 1,
				value);
      return (unsigned long) fixnum;
    }

  if (S48_BIGNUM_P(value)){
    bignum_type bignum = S48_ADDRESS_AFTER_HEADER(value, long);

    if (! s48_bignum_fits_in_word_p(bignum, 32, 0))
      s48_assertion_violation("s48_extract_unsigned_integer", "does not fit in word", 1,
			      value);
    else return s48_bignum_to_ulong(bignum);
  }
  else s48_assertion_violation("s48_extract_unsigned_integer", "not an exact integer", 1,
			       value);
}
