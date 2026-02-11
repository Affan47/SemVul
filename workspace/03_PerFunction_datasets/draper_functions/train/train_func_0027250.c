register_edge_assert_for (tree name, edge e, gimple_stmt_iterator si,
			  enum tree_code cond_code, tree cond_op0,
			  tree cond_op1)
{
  tree val;
  enum tree_code comp_code;
  bool retval = false;
  bool is_else_edge = (e->flags & EDGE_FALSE_VALUE) != 0;


  if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (name))
    return false;

  if (!extract_code_and_val_from_cond_with_ops (name, cond_code,
						cond_op0, cond_op1,
						is_else_edge,
						&comp_code, &val))
    return false;


  retval |= register_edge_assert_for_2 (name, e, si, cond_code, cond_op0,
					cond_op1, is_else_edge);


  if (((comp_code == EQ_EXPR && integer_onep (val))
       || (comp_code == NE_EXPR && integer_zerop (val))))
    {
      gimple def_stmt = SSA_NAME_DEF_STMT (name);

      if (is_gimple_assign (def_stmt)
	  && (gimple_assign_rhs_code (def_stmt) == TRUTH_AND_EXPR
	      || gimple_assign_rhs_code (def_stmt) == BIT_AND_EXPR))
	{
	  tree op0 = gimple_assign_rhs1 (def_stmt);
	  tree op1 = gimple_assign_rhs2 (def_stmt);
	  retval |= register_edge_assert_for_1 (op0, NE_EXPR, e, si);
	  retval |= register_edge_assert_for_1 (op1, NE_EXPR, e, si);
	}
    }


  if (((comp_code == EQ_EXPR && integer_zerop (val))
       || (comp_code == NE_EXPR && integer_onep (val))))
    {
      gimple def_stmt = SSA_NAME_DEF_STMT (name);

      if (is_gimple_assign (def_stmt)
	  && (gimple_assign_rhs_code (def_stmt) == TRUTH_OR_EXPR


	      || (comp_code == EQ_EXPR
		  && (gimple_assign_rhs_code (def_stmt) == BIT_IOR_EXPR))))
	{
	  tree op0 = gimple_assign_rhs1 (def_stmt);
	  tree op1 = gimple_assign_rhs2 (def_stmt);
	  retval |= register_edge_assert_for_1 (op0, EQ_EXPR, e, si);
	  retval |= register_edge_assert_for_1 (op1, EQ_EXPR, e, si);
	}
    }

  return retval;
}
