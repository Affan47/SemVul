rtl_unroll_and_peel_loops (void)
{
  if (number_of_loops () > 1)
    {
      int flags = 0;
      if (dump_file)
	df_dump (dump_file);

      if (flag_peel_loops)
	flags |= UAP_PEEL;
      if (flag_unroll_loops)
	flags |= UAP_UNROLL;
      if (flag_unroll_all_loops)
	flags |= UAP_UNROLL_ALL;

      unroll_and_peel_loops (flags);
    }
  return 0;
}
