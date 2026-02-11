ipa_analyze_call_uses (struct cgraph_node *node,
		       struct ipa_node_params *info,
		       struct param_analysis_info *parms_ainfo, gimple call)
{
  tree target = gimple_call_fn (call);

  if (!target)
    return;
  if (TREE_CODE (target) == SSA_NAME)
    ipa_analyze_indirect_call_uses (node, info, parms_ainfo, call, target);
  else if (TREE_CODE (target) == OBJ_TYPE_REF)
    ipa_analyze_virtual_call_uses (node, info, call, target);
}
