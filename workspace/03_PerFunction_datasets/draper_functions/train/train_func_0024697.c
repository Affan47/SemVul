collect_switch_conv_info (gimple swtch, struct switch_conv_info *info)
{
  unsigned int branch_num = gimple_switch_num_labels (swtch);
  tree min_case, max_case;
  unsigned int count, i;
  edge e, e_default;
  edge_iterator ei;

  memset (info, 0, sizeof (*info));


  info->index_expr = gimple_switch_index (swtch);
  info->switch_bb = gimple_bb (swtch);
  info->default_bb =
    label_to_block (CASE_LABEL (gimple_switch_default_label (swtch)));
  e_default = find_edge (info->switch_bb, info->default_bb);
  info->default_prob = e_default->probability;
  info->default_count = e_default->count;
  FOR_EACH_EDGE (e, ei, info->switch_bb->succs)
    if (e != e_default)
      info->other_count += e->count;


  FOR_EACH_EDGE (e, ei, info->switch_bb->succs)
    {
      if (! single_pred_p (e->dest))
	{
	  info->final_bb = e->dest;
	  break;
	}
    }
  if (info->final_bb)
    FOR_EACH_EDGE (e, ei, info->switch_bb->succs)
      {
	if (e->dest == info->final_bb)
	  continue;

	if (single_pred_p (e->dest)
	    && single_succ_p (e->dest)
	    && single_succ (e->dest) == info->final_bb)
	  continue;

	info->final_bb = NULL;
	break;
      }


  min_case = gimple_switch_label (swtch, 1);
  max_case = gimple_switch_label (swtch, branch_num - 1);

  info->range_min = CASE_LOW (min_case);
  if (CASE_HIGH (max_case) != NULL_TREE)
    info->range_max = CASE_HIGH (max_case);
  else
    info->range_max = CASE_LOW (max_case);

  info->range_size =
    int_const_binop (MINUS_EXPR, info->range_max, info->range_min);


  count = 0;
  for (i = 1; i < branch_num; i++)
    {
      tree elt = gimple_switch_label (swtch, i);
      count++;
      if (CASE_HIGH (elt)
	  && ! tree_int_cst_equal (CASE_LOW (elt), CASE_HIGH (elt)))
	count++;
    }
  info->count = count;


  info->uniq = EDGE_COUNT (gimple_bb (swtch)->succs) - 1;
}
