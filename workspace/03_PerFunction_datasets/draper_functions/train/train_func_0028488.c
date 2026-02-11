finish_omp_atomic (enum tree_code code, enum tree_code opcode, tree lhs,
		   tree rhs, tree v, tree lhs1, tree rhs1)
{
  tree orig_lhs;
  tree orig_rhs;
  tree orig_v;
  tree orig_lhs1;
  tree orig_rhs1;
  bool dependent_p;
  tree stmt;

  orig_lhs = lhs;
  orig_rhs = rhs;
  orig_v = v;
  orig_lhs1 = lhs1;
  orig_rhs1 = rhs1;
  dependent_p = false;
  stmt = NULL_TREE;


  if (processing_template_decl)
    {
      dependent_p = (type_dependent_expression_p (lhs)
		     || (rhs && type_dependent_expression_p (rhs))
		     || (v && type_dependent_expression_p (v))
		     || (lhs1 && type_dependent_expression_p (lhs1))
		     || (rhs1 && type_dependent_expression_p (rhs1)));
      if (!dependent_p)
	{
	  lhs = build_non_dependent_expr (lhs);
	  if (rhs)
	    rhs = build_non_dependent_expr (rhs);
	  if (v)
	    v = build_non_dependent_expr (v);
	  if (lhs1)
	    lhs1 = build_non_dependent_expr (lhs1);
	  if (rhs1)
	    rhs1 = build_non_dependent_expr (rhs1);
	}
    }
  if (!dependent_p)
    {
      stmt = c_finish_omp_atomic (input_location, code, opcode, lhs, rhs,
				  v, lhs1, rhs1);
      if (stmt == error_mark_node)
	return;
    }
  if (processing_template_decl)
    {
      if (code == OMP_ATOMIC_READ)
	{
	  stmt = build_min_nt_loc (EXPR_LOCATION (orig_lhs),
				   OMP_ATOMIC_READ, orig_lhs);
	  stmt = build2 (MODIFY_EXPR, void_type_node, orig_v, stmt);
	}
      else
	{
	  if (opcode == NOP_EXPR)
	    stmt = build2 (MODIFY_EXPR, void_type_node, orig_lhs, orig_rhs);
	  else
	    stmt = build2 (opcode, void_type_node, orig_lhs, orig_rhs);
	  if (orig_rhs1)
	    stmt = build_min_nt_loc (EXPR_LOCATION (orig_rhs1),
				     COMPOUND_EXPR, orig_rhs1, stmt);
	  if (code != OMP_ATOMIC)
	    {
	      stmt = build_min_nt_loc (EXPR_LOCATION (orig_lhs1),
				       code, orig_lhs1, stmt);
	      stmt = build2 (MODIFY_EXPR, void_type_node, orig_v, stmt);
	    }
	}
      stmt = build2 (OMP_ATOMIC, void_type_node, integer_zero_node, stmt);
    }
  finish_expr_stmt (stmt);
}
