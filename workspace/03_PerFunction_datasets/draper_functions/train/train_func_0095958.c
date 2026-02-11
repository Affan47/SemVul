decide_copy_try_finally (int ndests, bool may_throw, gimple_seq finally)
{
  int f_estimate, sw_estimate;
  gimple eh_else;


  eh_else = get_eh_else (finally);
  if (eh_else)
    {
      ndests -= may_throw;
      finally = gimple_eh_else_n_body (eh_else);
    }

  if (!optimize)
    {
      gimple_stmt_iterator gsi;

      if (ndests == 1)
        return true;

      for (gsi = gsi_start (finally); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple stmt = gsi_stmt (gsi);
	  if (!is_gimple_debug (stmt) && !gimple_clobber_p (stmt))
	    return false;
	}
      return true;
    }


  f_estimate = count_insns_seq (finally, &eni_size_weights);
  f_estimate = (f_estimate + 1) * ndests;


  sw_estimate = 10 + 2 * ndests;


  if (optimize_function_for_size_p (cfun))
    return f_estimate < sw_estimate;


  if (optimize > 1)
    return f_estimate < 100 || f_estimate < sw_estimate * 2;
  else
    return f_estimate < 40 || f_estimate * 2 < sw_estimate * 3;
}
