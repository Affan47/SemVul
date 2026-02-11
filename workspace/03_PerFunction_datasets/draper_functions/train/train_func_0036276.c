execute_compare_elim_after_reload (void)
{
  df_analyze ();

  gcc_checking_assert (!all_compares.exists ());


  find_comparisons ();
  if (all_compares.exists ())
    {
      struct comparison *cmp;
      size_t i;


      FOR_EACH_VEC_ELT (all_compares, i, cmp)
	{
	  try_eliminate_compare (cmp);
	  XDELETE (cmp);
	}

      all_compares.release ();
    }

  return 0;
}
