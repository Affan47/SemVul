tests_dbl_mant_bits (void)
{
  static int n = -1;
  volatile double x, y, d;

  if (n != -1)
    return n;

  n = 1;
  x = 2.0;
  for (;;)
    {


      y = x + 1.0;
      d = y - x;
      if (d != 1.0)
        {
#if defined (DBL_MANT_DIG) && DBL_RADIX == 2
          if (n != DBL_MANT_DIG)
            printf ("Warning, tests_dbl_mant_bits got %d but DBL_MANT_DIG says %d\n", n, DBL_MANT_DIG);
#endif
          break;
        }

      x *= 2;
      n++;

      if (n > 1000)
        {
          printf ("Oops, tests_dbl_mant_bits can't determine mantissa size\n");
          n = 0;
          break;
        }
    }
  return n;
}
