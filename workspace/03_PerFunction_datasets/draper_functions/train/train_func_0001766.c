find_candidates_in_block (struct dom_walk_data *walk_data ATTRIBUTE_UNUSED,
			  basic_block bb)
{
  bool speed = optimize_bb_for_speed_p (bb);
  gimple_stmt_iterator gsi;

  for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple gs = gsi_stmt (gsi);

      if (gimple_vuse (gs) && gimple_assign_single_p (gs))
	slsr_process_ref (gs);

      else if (is_gimple_assign (gs)
	       && SCALAR_INT_MODE_P
	            (TYPE_MODE (TREE_TYPE (gimple_assign_lhs (gs)))))
	{
	  tree rhs1 = NULL_TREE, rhs2 = NULL_TREE;

	  switch (gimple_assign_rhs_code (gs))
	    {
	    case MULT_EXPR:
	    case PLUS_EXPR:
	      rhs1 = gimple_assign_rhs1 (gs);
	      rhs2 = gimple_assign_rhs2 (gs);


	      if (TREE_CODE (rhs1) != SSA_NAME)
		continue;
	      break;


	    case POINTER_PLUS_EXPR:
	    case MINUS_EXPR:
	      rhs2 = gimple_assign_rhs2 (gs);


	    case NOP_EXPR:
	    case MODIFY_EXPR:
	    case NEGATE_EXPR:
	      rhs1 = gimple_assign_rhs1 (gs);
	      if (TREE_CODE (rhs1) != SSA_NAME)
		continue;
	      break;

	    default:
	      ;
	    }

	  switch (gimple_assign_rhs_code (gs))
	    {
	    case MULT_EXPR:
	      slsr_process_mul (gs, rhs1, rhs2, speed);
	      break;

	    case PLUS_EXPR:
	    case POINTER_PLUS_EXPR:
	    case MINUS_EXPR:
	      slsr_process_add (gs, rhs1, rhs2, speed);
	      break;

	    case NEGATE_EXPR:
	      slsr_process_neg (gs, rhs1, speed);
	      break;

	    case NOP_EXPR:
	      slsr_process_cast (gs, rhs1, speed);
	      break;

	    case MODIFY_EXPR:
	      slsr_process_copy (gs, rhs1, speed);
	      break;

	    default:
	      ;
	    }
	}
    }
}
