forward_propagate_into_cond (gimple_stmt_iterator *gsi_p)
{
  gimple stmt = gsi_stmt (*gsi_p);
  tree tmp = NULL_TREE;
  tree cond = gimple_assign_rhs1 (stmt);
  enum tree_code code = gimple_assign_rhs_code (stmt);
  bool swap = false;


  if (COMPARISON_CLASS_P (cond))
    tmp = forward_propagate_into_comparison_1 (stmt, TREE_CODE (cond),
					       TREE_TYPE (cond),
					       TREE_OPERAND (cond, 0),
					       TREE_OPERAND (cond, 1));
  else if (TREE_CODE (cond) == SSA_NAME)
    {
      enum tree_code def_code;
      tree name = cond;
      gimple def_stmt = get_prop_source_stmt (name, true, NULL);
      if (!def_stmt || !can_propagate_from (def_stmt))
	return 0;

      def_code = gimple_assign_rhs_code (def_stmt);
      if (TREE_CODE_CLASS (def_code) == tcc_comparison)
	tmp = fold_build2_loc (gimple_location (def_stmt),
			       def_code,
			       TREE_TYPE (cond),
			       gimple_assign_rhs1 (def_stmt),
			       gimple_assign_rhs2 (def_stmt));
      else if (code == COND_EXPR
	       && ((def_code == BIT_NOT_EXPR
		    && TYPE_PRECISION (TREE_TYPE (cond)) == 1)
		   || (def_code == BIT_XOR_EXPR
		       && integer_onep (gimple_assign_rhs2 (def_stmt)))))
	{
	  tmp = gimple_assign_rhs1 (def_stmt);
	  swap = true;
	}
    }

  if (tmp
      && is_gimple_condexpr (tmp))
    {
      if (dump_file && tmp)
	{
	  fprintf (dump_file, "  Replaced '");
	  print_generic_expr (dump_file, cond, 0);
	  fprintf (dump_file, "' with '");
	  print_generic_expr (dump_file, tmp, 0);
	  fprintf (dump_file, "'\n");
	}

      if ((code == VEC_COND_EXPR) ? integer_all_onesp (tmp)
				  : integer_onep (tmp))
	gimple_assign_set_rhs_from_tree (gsi_p, gimple_assign_rhs2 (stmt));
      else if (integer_zerop (tmp))
	gimple_assign_set_rhs_from_tree (gsi_p, gimple_assign_rhs3 (stmt));
      else
	{
	  gimple_assign_set_rhs1 (stmt, unshare_expr (tmp));
	  if (swap)
	    {
	      tree t = gimple_assign_rhs2 (stmt);
	      gimple_assign_set_rhs2 (stmt, gimple_assign_rhs3 (stmt));
	      gimple_assign_set_rhs3 (stmt, t);
	    }
	}
      stmt = gsi_stmt (*gsi_p);
      update_stmt (stmt);

      return true;
    }

  return 0;
}
