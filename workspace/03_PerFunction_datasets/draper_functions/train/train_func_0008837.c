init_vn_nary_op_from_stmt (vn_nary_op_t vno, gimple stmt)
{
  unsigned i;

  vno->opcode = gimple_assign_rhs_code (stmt);
  vno->type = gimple_expr_type (stmt);
  switch (vno->opcode)
    {
    case REALPART_EXPR:
    case IMAGPART_EXPR:
    case VIEW_CONVERT_EXPR:
      vno->length = 1;
      vno->op[0] = TREE_OPERAND (gimple_assign_rhs1 (stmt), 0);
      break;

    case BIT_FIELD_REF:
      vno->length = 3;
      vno->op[0] = TREE_OPERAND (gimple_assign_rhs1 (stmt), 0);
      vno->op[1] = TREE_OPERAND (gimple_assign_rhs1 (stmt), 1);
      vno->op[2] = TREE_OPERAND (gimple_assign_rhs1 (stmt), 2);
      break;

    case CONSTRUCTOR:
      vno->length = CONSTRUCTOR_NELTS (gimple_assign_rhs1 (stmt));
      for (i = 0; i < vno->length; ++i)
	vno->op[i] = CONSTRUCTOR_ELT (gimple_assign_rhs1 (stmt), i)->value;
      break;

    default:
      gcc_checking_assert (!gimple_assign_single_p (stmt));
      vno->length = gimple_num_ops (stmt) - 1;
      for (i = 0; i < vno->length; ++i)
	vno->op[i] = gimple_op (stmt, i + 1);
    }
}
