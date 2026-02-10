init_vn_nary_op_from_stmt (vn_nary_op_t vno, gimple stmt)
{
  unsigned i;

  vno->opcode = gimple_assign_rhs_code (stmt);
  vno->length = gimple_num_ops (stmt) - 1;
  vno->type = gimple_expr_type (stmt);
  for (i = 0; i < vno->length; ++i)
    vno->op[i] = gimple_op (stmt, i + 1);
  if (vno->opcode == REALPART_EXPR
      || vno->opcode == IMAGPART_EXPR
      || vno->opcode == VIEW_CONVERT_EXPR)
    vno->op[0] = TREE_OPERAND (vno->op[0], 0);
}
