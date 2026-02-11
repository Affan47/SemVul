build_address (tree t)
{
  if (error_operand_p (t) || !cxx_mark_addressable (t))
    return error_mark_node;
  t = build_fold_addr_expr (t);
  if (TREE_CODE (t) != ADDR_EXPR)
    t = rvalue (t);
  return t;
}
