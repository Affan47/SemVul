build_x_compound_expr (tree op1, tree op2, tsubst_flags_t complain)
{
  tree result;
  tree orig_op1 = op1;
  tree orig_op2 = op2;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (op1)
	  || type_dependent_expression_p (op2))
	return build_min_nt (COMPOUND_EXPR, op1, op2);
      op1 = build_non_dependent_expr (op1);
      op2 = build_non_dependent_expr (op2);
    }

  result = build_new_op (COMPOUND_EXPR, LOOKUP_NORMAL, op1, op2, NULL_TREE,
			 NULL, complain);
  if (!result)
    result = cp_build_compound_expr (op1, op2, complain);

  if (processing_template_decl && result != error_mark_node)
    return build_min_non_dep (COMPOUND_EXPR, result, orig_op1, orig_op2);

  return result;
}
