find_switch_asserts (basic_block bb, gimple last)
{
  bool need_assert;
  gimple_stmt_iterator bsi;
  tree op;
  edge e;
  struct case_info *ci;
  size_t n = gimple_switch_num_labels (last);
#if GCC_VERSION >= 4000
  unsigned int idx;
#else

  volatile unsigned int idx;
#endif

  need_assert = false;
  bsi = gsi_for_stmt (last);
  op = gimple_switch_index (last);
  if (TREE_CODE (op) != SSA_NAME)
    return false;


  ci = XNEWVEC (struct case_info, n);
  for (idx = 0; idx < n; ++idx)
    {
      ci[idx].expr = gimple_switch_label (last, idx);
      ci[idx].bb = label_to_block (CASE_LABEL (ci[idx].expr));
    }
  qsort (ci, n, sizeof (struct case_info), compare_case_labels);

  for (idx = 0; idx < n; ++idx)
    {
      tree min, max;
      tree cl = ci[idx].expr;
      basic_block cbb = ci[idx].bb;

      min = CASE_LOW (cl);
      max = CASE_HIGH (cl);


      if (idx + 1 < n && cbb == ci[idx + 1].bb)
	{

	  do {
	    ++idx;
	  } while (idx < n && cbb == ci[idx].bb);
	  --idx;


	  if (CASE_HIGH (ci[idx].expr))
	    max = CASE_HIGH (ci[idx].expr);
	  else
	    max = CASE_LOW (ci[idx].expr);
	}


      if (min == NULL_TREE)
	continue;


      e = find_edge (bb, cbb);


      need_assert |= register_edge_assert_for (op, e, bsi,
					       max ? GE_EXPR : EQ_EXPR,
					       op,
					       fold_convert (TREE_TYPE (op),
							     min));
      if (max)
	{
	  need_assert |= register_edge_assert_for (op, e, bsi, LE_EXPR,
						   op,
						   fold_convert (TREE_TYPE (op),
								 max));
	}
    }

  XDELETEVEC (ci);
  return need_assert;
}
