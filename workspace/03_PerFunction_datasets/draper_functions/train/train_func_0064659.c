build_compound_expr (tree result_type, tree stmt_operand, tree expr_operand)
{
  bool addr_p = false;
  tree result;


  if (TREE_CODE (result_type) == UNCONSTRAINED_ARRAY_TYPE
      || CONTAINS_PLACEHOLDER_P (TYPE_SIZE (result_type)))
    {
      result_type = build_pointer_type (result_type);
      expr_operand = build_unary_op (ADDR_EXPR, result_type, expr_operand);
      addr_p = true;
    }

  result = fold_build2 (COMPOUND_EXPR, result_type, stmt_operand,
			expr_operand);

  if (addr_p)
    result = build_unary_op (INDIRECT_REF, NULL_TREE, result);

  return result;
}
