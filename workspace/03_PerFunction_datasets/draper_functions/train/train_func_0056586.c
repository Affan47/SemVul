tcmp2 (double x, double y, int i)
{
  mpfr_t xx, yy;
  mpfr_prec_t j;

  if (i == -1)
    {
      if (x == y)
        i = 53;
      else
        i = (int) (__gmpfr_floor_log2 (x) - __gmpfr_floor_log2 (x - y));
    }
  mpfr_init2(xx, 53); mpfr_init2(yy, 53);
  mpfr_set_d (xx, x, MPFR_RNDN);
  mpfr_set_d (yy, y, MPFR_RNDN);
  j = 0;
  if (mpfr_cmp2 (xx, yy, &j) == 0)
    {
      if (x != y)
        {
          printf ("Error in mpfr_cmp2 for\nx=");
          mpfr_out_str (stdout, 2, 0, xx, MPFR_RNDN);
          printf ("\ny=");
          mpfr_out_str (stdout, 2, 0, yy, MPFR_RNDN);
          printf ("\ngot sign 0 for x != y\n");
          exit (1);
        }
    }
  else if (j != (unsigned) i)
    {
      printf ("Error in mpfr_cmp2 for\nx=");
      mpfr_out_str (stdout, 2, 0, xx, MPFR_RNDN);
      printf ("\ny=");
      mpfr_out_str (stdout, 2, 0, yy, MPFR_RNDN);
      printf ("\ngot %lu instead of %d\n", (unsigned long) j, i);
      exit (1);
    }
  mpfr_clear(xx); mpfr_clear(yy);
}
