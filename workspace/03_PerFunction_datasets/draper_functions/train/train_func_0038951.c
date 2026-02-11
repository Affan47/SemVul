bignum_divide(bignum_type numerator, bignum_type denominator,
                  bignum_type * quotient, bignum_type * remainder)
{
  if (BIGNUM_ZERO_P (denominator))
    {
      divide_by_zero_error();
      return;
    }
  if (BIGNUM_ZERO_P (numerator))
    {
      (*quotient) = numerator;
      (*remainder) = numerator;
    }
  else
    {
      int r_negative_p = (BIGNUM_NEGATIVE_P (numerator));
      int q_negative_p =
        ((BIGNUM_NEGATIVE_P (denominator)) ? (! r_negative_p) : r_negative_p);
      switch (bignum_compare_unsigned (numerator, denominator))
        {
        case bignum_comparison_equal:
          {
            (*quotient) = (BIGNUM_ONE (q_negative_p));
            (*remainder) = (BIGNUM_ZERO ());
            break;
          }
        case bignum_comparison_less:
          {
            (*quotient) = (BIGNUM_ZERO ());
            (*remainder) = numerator;
            break;
          }
        case bignum_comparison_greater:
          {
            if ((BIGNUM_LENGTH (denominator)) == 1)
              {
                bignum_digit_type digit = (BIGNUM_REF (denominator, 0));
                if (digit == 1)
                  {
                    (*quotient) =
                      (bignum_maybe_new_sign (numerator, q_negative_p));
                    (*remainder) = (BIGNUM_ZERO ());
                    break;
                  }
                else if (digit < BIGNUM_RADIX_ROOT)
                  {
                    bignum_divide_unsigned_small_denominator
                      (numerator, digit,
                       quotient, remainder,
                       q_negative_p, r_negative_p);
                    break;
                  }
                else
                  {
                    bignum_divide_unsigned_medium_denominator
                      (numerator, digit,
                       quotient, remainder,
                       q_negative_p, r_negative_p);
                    break;
                  }
              }
            bignum_divide_unsigned_large_denominator
              (numerator, denominator,
               quotient, remainder,
               q_negative_p, r_negative_p);
            break;
          }
        }
    }
}
