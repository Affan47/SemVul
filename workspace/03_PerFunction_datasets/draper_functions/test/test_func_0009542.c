get_index_from_offset (tree offset, gimple def_stmt)
{
  tree op1, op2, index;

  if (gimple_code (def_stmt) == GIMPLE_PHI)
    return NULL;
  if ((gimple_assign_copy_p (def_stmt) || gimple_assign_cast_p (def_stmt))
      && TREE_CODE (gimple_assign_rhs1 (def_stmt)) == SSA_NAME)
    return get_index_from_offset (offset,
				  SSA_NAME_DEF_STMT (gimple_assign_rhs1 (def_stmt)));
  else if (is_gimple_assign (def_stmt)
	   && gimple_assign_rhs_code (def_stmt) == MULT_EXPR)
    {
      op1 = gimple_assign_rhs1 (def_stmt);
      op2 = gimple_assign_rhs2 (def_stmt);
      if (TREE_CODE (op1) != INTEGER_CST && TREE_CODE (op2) != INTEGER_CST)
	return NULL;
      index = (TREE_CODE (op1) == INTEGER_CST) ? op2 : op1;
      return index;
    }
  else
    return NULL_TREE;
}
