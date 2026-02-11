bignum_equal_p_unsigned(bignum_type x, bignum_type y)
{
  bignum_length_type length = (BIGNUM_LENGTH (x));
  if (length != (BIGNUM_LENGTH (y)))
    return (0);
  else
    {
      bignum_digit_type * scan_x = (BIGNUM_START_PTR (x));
      bignum_digit_type * scan_y = (BIGNUM_START_PTR (y));
      bignum_digit_type * end_x = (scan_x + length);
      while (scan_x < end_x)
        if ((*scan_x++) != (*scan_y++))
          return (0);
      return (1);
    }
}
