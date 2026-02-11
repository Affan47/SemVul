load_from_unmodified_param (struct ipa_node_params *info,
			    struct param_analysis_info *parms_ainfo,
			    gimple stmt)
{
  int index;
  tree op1;

  if (!gimple_assign_single_p (stmt))
    return -1;

  op1 = gimple_assign_rhs1 (stmt);
  if (TREE_CODE (op1) != PARM_DECL)
    return -1;

  index = ipa_get_param_decl_index (info, op1);
  if (index < 0
      || is_parm_modified_before_stmt (&parms_ainfo[index], stmt, op1))
    return -1;

  return index;
}
