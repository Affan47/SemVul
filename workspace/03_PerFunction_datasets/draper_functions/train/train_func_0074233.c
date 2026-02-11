break_up_subtract_bb (basic_block bb)
{
  gimple_stmt_iterator gsi;
  basic_block son;

  for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple stmt = gsi_stmt (gsi);
      gimple_set_visited (stmt, false);

      if (!is_gimple_assign (stmt)
	  || !can_reassociate_p (gimple_assign_lhs (stmt)))
	continue;


      if (gimple_assign_rhs_code (stmt) == MINUS_EXPR)
	{
	  if (!can_reassociate_p (gimple_assign_rhs1 (stmt))
	      || !can_reassociate_p (gimple_assign_rhs2 (stmt)))
	    continue;


	  if (should_break_up_subtract (stmt))
	    break_up_subtract (stmt, &gsi);
	}
      else if (gimple_assign_rhs_code (stmt) == NEGATE_EXPR
	       && can_reassociate_p (gimple_assign_rhs1 (stmt)))
	VEC_safe_push (tree, heap, plus_negates, gimple_assign_lhs (stmt));
    }
  for (son = first_dom_son (CDI_DOMINATORS, bb);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    break_up_subtract_bb (son);
}
