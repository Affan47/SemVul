check_clz (int want, mp_limb_t n)
{
  int  got;
  count_leading_zeros (got, n);
  if (got != want)
    {
      printf        ("count_leading_zeros wrong\n");
      mp_limb_trace ("  n    ", n);
      printf        ("  want %d\n", want);
      printf        ("  got  %d\n", got);
      abort ();
    }
}
