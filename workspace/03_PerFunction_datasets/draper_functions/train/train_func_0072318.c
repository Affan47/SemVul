simple_strtod_human (const char *input_str,
                     char **endptr, long double *value, size_t *precision,
                     enum scale_type allowed_scaling)
{
  int power = 0;

  int scale_base = default_scale_base (allowed_scaling);

  devmsg ("simple_strtod_human:\n  input string: '%s'\n  "
          "locale decimal-point: '%s'\n", input_str, decimal_point);

  enum simple_strtod_error e =
    simple_strtod_float (input_str, endptr, value, precision);
  if (e != SSE_OK && e != SSE_OK_PRECISION_LOSS)
    return e;

  devmsg ("  parsed numeric value: %Lf\n"
          "  input precision = %d\n", *value, (int)*precision);

  if (**endptr != '\0')
    {


      while (isblank (**endptr))
        (*endptr)++;

      if (!valid_suffix (**endptr))
        return SSE_INVALID_SUFFIX;

      if (allowed_scaling == scale_none)
        return SSE_VALID_BUT_FORBIDDEN_SUFFIX;

      power = suffix_power (**endptr);
      (*endptr)++;

      if (allowed_scaling == scale_auto && **endptr == 'i')
        {


          scale_base = 1024;
          (*endptr)++;
          devmsg ("  Auto-scaling, found 'i', switching to base %d\n",
                  scale_base);
        }

      *precision = 0;
    }

  if (allowed_scaling == scale_IEC_I)
    {
      if (**endptr == 'i')
        (*endptr)++;
      else
        return SSE_MISSING_I_SUFFIX;
    }

  long double multiplier = powerld (scale_base, power);

  devmsg ("  suffix power=%d^%d = %Lf\n", scale_base, power, multiplier);


  (*value) = (*value) * multiplier;

  devmsg ("  returning value: %Lf (%LG)\n", *value, *value);

  return e;
}
