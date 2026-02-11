bignum_add_unsigned(bignum_type x, bignum_type y, int negative_p)
{
  if ((BIGNUM_LENGTH (y)) > (BIGNUM_LENGTH (x)))
    {
      bignum_type z = x;
      x = y;
      y = z;
    }
  {
    bignum_length_type x_length = (BIGNUM_LENGTH (x));

    REGISTER_BIGNUM(x);
    REGISTER_BIGNUM(y);
    bignum_type r = (allot_bignum ((x_length + 1), negative_p));
    UNREGISTER_BIGNUM(y);
    UNREGISTER_BIGNUM(x);

    bignum_digit_type sum;
    bignum_digit_type carry = 0;
    bignum_digit_type * scan_x = (BIGNUM_START_PTR (x));
    bignum_digit_type * scan_r = (BIGNUM_START_PTR (r));
    {
      bignum_digit_type * scan_y = (BIGNUM_START_PTR (y));
      bignum_digit_type * end_y = (scan_y + (BIGNUM_LENGTH (y)));
      while (scan_y < end_y)
        {
          sum = ((*scan_x++) + (*scan_y++) + carry);
          if (sum < BIGNUM_RADIX)
            {
              (*scan_r++) = sum;
              carry = 0;
            }
          else
            {
              (*scan_r++) = (sum - BIGNUM_RADIX);
              carry = 1;
            }
        }
    }
    {
      bignum_digit_type * end_x = ((BIGNUM_START_PTR (x)) + x_length);
      if (carry != 0)
        while (scan_x < end_x)
          {
            sum = ((*scan_x++) + 1);
            if (sum < BIGNUM_RADIX)
              {
                (*scan_r++) = sum;
                carry = 0;
                break;
              }
            else
              (*scan_r++) = (sum - BIGNUM_RADIX);
          }
      while (scan_x < end_x)
        (*scan_r++) = (*scan_x++);
    }
    if (carry != 0)
      {
        (*scan_r) = 1;
        return (r);
      }
    return (bignum_shorten_length (r, x_length));
  }
}
