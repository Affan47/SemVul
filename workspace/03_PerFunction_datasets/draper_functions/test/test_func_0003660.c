will_be_nonconstant_expr_predicate (struct ipa_node_params *info,
				    struct inline_summary *summary,
				    tree expr,
				    vec<predicate_t> nonconstant_names)
{
  tree parm;
  int index;

  while (UNARY_CLASS_P (expr))
    expr = TREE_OPERAND (expr, 0);

  parm = unmodified_parm (NULL, expr);
  if (parm && (index = ipa_get_param_decl_index (info, parm)) >= 0)
    return add_condition (summary, index, NULL, CHANGED, NULL_TREE);
  if (is_gimple_min_invariant (expr))
    return false_predicate ();
  if (TREE_CODE (expr) == SSA_NAME)
    return nonconstant_names[SSA_NAME_VERSION (expr)];
  if (BINARY_CLASS_P (expr) || COMPARISON_CLASS_P (expr))
    {
      struct predicate p1 = will_be_nonconstant_expr_predicate
	(info, summary, TREE_OPERAND (expr, 0),
	 nonconstant_names);
      struct predicate p2;
      if (true_predicate_p (&p1))
	return p1;
      p2 = will_be_nonconstant_expr_predicate (info, summary,
					       TREE_OPERAND (expr, 1),
					       nonconstant_names);
      return or_predicates (summary->conds, &p1, &p2);
    }
  else if (TREE_CODE (expr) == COND_EXPR)
    {
      struct predicate p1 = will_be_nonconstant_expr_predicate
	(info, summary, TREE_OPERAND (expr, 0),
	 nonconstant_names);
      struct predicate p2;
      if (true_predicate_p (&p1))
	return p1;
      p2 = will_be_nonconstant_expr_predicate (info, summary,
					       TREE_OPERAND (expr, 1),
					       nonconstant_names);
      if (true_predicate_p (&p2))
	return p2;
      p1 = or_predicates (summary->conds, &p1, &p2);
      p2 = will_be_nonconstant_expr_predicate (info, summary,
					       TREE_OPERAND (expr, 2),
					       nonconstant_names);
      return or_predicates (summary->conds, &p1, &p2);
    }
  else
    {
      debug_tree (expr);
      gcc_unreachable ();
    }
  return false_predicate ();
}
