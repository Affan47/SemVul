bignum_magnitude_ash(bignum* arg1, fixnum n) {
  GC_BIGNUM(arg1);

  bignum* result = NULL;
  bignum_digit_type* scan1;
  bignum_digit_type* scanr;
  bignum_digit_type* end;

  fixnum digit_offset, bit_offset;

  if (BIGNUM_ZERO_P(arg1))
    return (arg1);

  if (n > 0) {
    digit_offset = n / BIGNUM_DIGIT_LENGTH;
    bit_offset = n % BIGNUM_DIGIT_LENGTH;

    result = allot_bignum_zeroed(BIGNUM_LENGTH(arg1) + digit_offset + 1,
                                 BIGNUM_NEGATIVE_P(arg1));

    scanr = BIGNUM_START_PTR(result) + digit_offset;
    scan1 = BIGNUM_START_PTR(arg1);
    end = scan1 + BIGNUM_LENGTH(arg1);

    while (scan1 < end) {
      *scanr = *scanr | (*scan1 & BIGNUM_DIGIT_MASK) << bit_offset;
      *scanr = *scanr & BIGNUM_DIGIT_MASK;
      scanr++;
      *scanr = *scan1++ >> (BIGNUM_DIGIT_LENGTH - bit_offset);
      *scanr = *scanr & BIGNUM_DIGIT_MASK;
    }
  } else if (n < 0 && (-n >= (BIGNUM_LENGTH(arg1) * (bignum_length_type)
                              BIGNUM_DIGIT_LENGTH)))
    result = BIGNUM_ZERO();

  else if (n < 0) {
    digit_offset = -n / BIGNUM_DIGIT_LENGTH;
    bit_offset = -n % BIGNUM_DIGIT_LENGTH;

    result = allot_bignum_zeroed(BIGNUM_LENGTH(arg1) - digit_offset,
                                 BIGNUM_NEGATIVE_P(arg1));

    scanr = BIGNUM_START_PTR(result);
    scan1 = BIGNUM_START_PTR(arg1) + digit_offset;
    end = scanr + BIGNUM_LENGTH(result) - 1;

    while (scanr < end) {
      *scanr = (*scan1++ & BIGNUM_DIGIT_MASK) >> bit_offset;
      *scanr = (*scanr | *scan1 << (BIGNUM_DIGIT_LENGTH - bit_offset)) &
               BIGNUM_DIGIT_MASK;
      scanr++;
    }
    *scanr = (*scan1++ & BIGNUM_DIGIT_MASK) >> bit_offset;
  } else if (n == 0)
    result = arg1;

  return (bignum_trim(result));
}
