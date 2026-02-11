ipa_analyze_stmt_uses (struct cgraph_node *node, struct ipa_node_params *info,
		       struct param_analysis_info *parms_ainfo, gimple stmt)
{
  if (is_gimple_call (stmt))
    ipa_analyze_call_uses (node, info, parms_ainfo, stmt);
}
