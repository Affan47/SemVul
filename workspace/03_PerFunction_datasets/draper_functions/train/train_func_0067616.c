check_ctz (int want, mp_limb_t n)
{
  int  got;
  count_trailing_zeros (got, n);
  if (got != want)
    {
      printf ("count_trailing_zeros wrong\n");
      mpn_trace ("  n    ", &n, (mp_size_t) 1);
      printf    ("  want %d\n", want);
      printf    ("  got  %d\n", got);
      abort ();
    }
}
