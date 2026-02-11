ssa_accessed_in_assign_rhs (gimple stmt, struct ssa_acc_in_tree *a)
{

  a->t_code = gimple_assign_rhs_code (stmt);
  switch (a->t_code)
    {
      tree op1, op2;

    case SSA_NAME:
    case MEM_REF:
    CASE_CONVERT:
    case VIEW_CONVERT_EXPR:
      ssa_accessed_in_tree (gimple_assign_rhs1 (stmt), a);
      break;
    case POINTER_PLUS_EXPR:
    case PLUS_EXPR:
    case MULT_EXPR:
      op1 = gimple_assign_rhs1 (stmt);
      op2 = gimple_assign_rhs2 (stmt);

      if (op1 == a->ssa_var)
	{
	  a->var_found = true;
	  a->second_op = op2;
	}
      else if (op2 == a->ssa_var)
	{
	  a->var_found = true;
	  a->second_op = op1;
	}
      break;
    default:
      break;
    }
}
