bignum_unsigned_logcount(bignum_type arg)
{

  bignum_digit_type *scan;
  bignum_digit_type *end;
  bignum_digit_type digit;


  long result;
  unsigned long i;

  if (BIGNUM_ZERO_P (arg)) return (0L);

  scan = BIGNUM_START_PTR (arg);
  end = scan + BIGNUM_LENGTH (arg);
  result = 0L;

  while (scan < end) {
      digit = *scan++ & BIGNUM_DIGIT_MASK;
      for (i = 0; i++ < BIGNUM_DIGIT_LENGTH; digit = digit >> 1L)
	  result += digit & 1L;
  }

  return (result);
}
