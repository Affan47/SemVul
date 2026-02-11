simple_strtod_float (const char *input_str,
                     char **endptr,
                     long double *value,
                     size_t *precision)
{
  bool negative;
  enum simple_strtod_error e = SSE_OK;

  if (precision)
    *precision = 0;


  e = simple_strtod_int (input_str, endptr, value, &negative);
  if (e != SSE_OK && e != SSE_OK_PRECISION_LOSS)
    return e;


  if (STREQ_LEN (*endptr, decimal_point, decimal_point_length))
    {
      char *ptr2;
      long double val_frac = 0;
      bool neg_frac;

      (*endptr) += decimal_point_length;
      enum simple_strtod_error e2 =
        simple_strtod_int (*endptr, &ptr2, &val_frac, &neg_frac);
      if (e2 != SSE_OK && e2 != SSE_OK_PRECISION_LOSS)
        return e2;
      if (e2 == SSE_OK_PRECISION_LOSS)
        e = e2;
      if (neg_frac)
        return SSE_INVALID_NUMBER;


      size_t exponent = ptr2 - *endptr;

      val_frac = ((long double) val_frac) / powerld (10, exponent);

      if (value)
        {
          if (negative)
            *value -= val_frac;
          else
            *value += val_frac;
        }

      if (precision)
        *precision = exponent;

      *endptr = ptr2;
    }
  return e;
}
