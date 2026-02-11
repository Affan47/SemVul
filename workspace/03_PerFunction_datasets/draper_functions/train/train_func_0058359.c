bignum_compare_unsigned(bignum_type x, bignum_type y)
{
  bignum_length_type x_length = (BIGNUM_LENGTH (x));
  bignum_length_type y_length = (BIGNUM_LENGTH (y));
  if (x_length < y_length)
    return (bignum_comparison_less);
  if (x_length > y_length)
    return (bignum_comparison_greater);
  {
    bignum_digit_type * start_x = (BIGNUM_START_PTR (x));
    bignum_digit_type * scan_x = (start_x + x_length);
    bignum_digit_type * scan_y = ((BIGNUM_START_PTR (y)) + y_length);
    while (start_x < scan_x)
      {
	bignum_digit_type digit_x = (*--scan_x);
	bignum_digit_type digit_y = (*--scan_y);
	if (digit_x < digit_y)
	  return (bignum_comparison_less);
	if (digit_x > digit_y)
	  return (bignum_comparison_greater);
      }
  }
  return (bignum_comparison_equal);
}
