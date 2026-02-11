check_worst_case (const char *Xs, const char *expxs)
{
  mpfr_t x, y;

  mpfr_inits2 (53, x, y, (mpfr_ptr) 0);
  mpfr_set_str1(x, Xs);
  test_exp(y, x, MPFR_RNDD);
  if (mpfr_cmp_str1 (y, expxs))
    {
      printf ("exp(x) rounded toward -infinity is wrong\n");
      exit(1);
    }
  mpfr_set_str1(x, Xs);
  test_exp(x, x, MPFR_RNDU);
  mpfr_nexttoinf (y);
  if (mpfr_cmp(x,y))
    {
      printf ("exp(x) rounded toward +infinity is wrong\n");
      exit(1);
    }
  mpfr_clears (x, y, (mpfr_ptr) 0);
}
