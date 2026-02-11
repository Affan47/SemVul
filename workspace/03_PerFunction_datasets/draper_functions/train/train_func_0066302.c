gimple_ic_transform (gimple stmt)
{
  histogram_value histogram;
  gcov_type val, count, all, bb_all;
  gcov_type prob;
  gimple modify;
  struct cgraph_node *direct_call;

  if (gimple_code (stmt) != GIMPLE_CALL)
    return false;

  if (gimple_call_fndecl (stmt) != NULL_TREE)
    return false;

  if (gimple_call_internal_p (stmt))
    return false;

  histogram = gimple_histogram_value_of_type (cfun, stmt, HIST_TYPE_INDIR_CALL);
  if (!histogram)
    return false;

  val = histogram->hvalue.counters [0];
  count = histogram->hvalue.counters [1];
  all = histogram->hvalue.counters [2];
  gimple_remove_histogram_value (cfun, stmt, histogram);

  if (4 * count <= 3 * all)
    return false;

  bb_all = gimple_bb (stmt)->count;


  if ( check_counter (stmt, "ic", &all, &bb_all, bb_all)
      || check_counter (stmt, "ic", &count, &all, all))
    return false;

  if (all > 0)
    prob = (count * REG_BR_PROB_BASE + all / 2) / all;
  else
    prob = 0;
  direct_call = find_func_by_funcdef_no ((int)val);

  if (direct_call == NULL)
    return false;

  if (!check_ic_target (stmt, direct_call))
    return false;

  modify = gimple_ic (stmt, direct_call, prob, count, all);

  if (dump_file)
    {
      fprintf (dump_file, "Indirect call -> direct call ");
      print_generic_expr (dump_file, gimple_call_fn (stmt), TDF_SLIM);
      fprintf (dump_file, "=> ");
      print_generic_expr (dump_file, direct_call->decl, TDF_SLIM);
      fprintf (dump_file, " transformation on insn ");
      print_gimple_stmt (dump_file, stmt, 0, TDF_SLIM);
      fprintf (dump_file, " to ");
      print_gimple_stmt (dump_file, modify, 0, TDF_SLIM);
      fprintf (dump_file, "hist->count "HOST_WIDEST_INT_PRINT_DEC
	       " hist->all "HOST_WIDEST_INT_PRINT_DEC"\n", count, all);
    }

  return true;
}
