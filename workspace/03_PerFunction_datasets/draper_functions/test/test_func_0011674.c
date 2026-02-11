ifcombine_ifandif (basic_block inner_cond_bb, basic_block outer_cond_bb)
{
  gimple_stmt_iterator gsi;
  gimple inner_cond, outer_cond;
  tree name1, name2, bit1, bit2;

  inner_cond = last_stmt (inner_cond_bb);
  if (!inner_cond
      || gimple_code (inner_cond) != GIMPLE_COND)
    return false;

  outer_cond = last_stmt (outer_cond_bb);
  if (!outer_cond
      || gimple_code (outer_cond) != GIMPLE_COND)
    return false;


  if (recognize_single_bit_test (inner_cond, &name1, &bit1)
      && recognize_single_bit_test (outer_cond, &name2, &bit2)
      && name1 == name2)
    {
      tree t, t2;


      gsi = gsi_for_stmt (inner_cond);
      t = fold_build2 (LSHIFT_EXPR, TREE_TYPE (name1),
		       build_int_cst (TREE_TYPE (name1), 1), bit1);
      t2 = fold_build2 (LSHIFT_EXPR, TREE_TYPE (name1),
		        build_int_cst (TREE_TYPE (name1), 1), bit2);
      t = fold_build2 (BIT_IOR_EXPR, TREE_TYPE (name1), t, t2);
      t = force_gimple_operand_gsi (&gsi, t, true, NULL_TREE,
				    true, GSI_SAME_STMT);
      t2 = fold_build2 (BIT_AND_EXPR, TREE_TYPE (name1), name1, t);
      t2 = force_gimple_operand_gsi (&gsi, t2, true, NULL_TREE,
				     true, GSI_SAME_STMT);
      t = fold_build2 (EQ_EXPR, boolean_type_node, t2, t);
      t = canonicalize_cond_expr_cond (t);
      if (!t)
	return false;
      gimple_cond_set_condition_from_tree (inner_cond, t);
      update_stmt (inner_cond);


      gimple_cond_set_condition_from_tree (outer_cond, boolean_true_node);
      update_stmt (outer_cond);

      if (dump_file)
	{
	  fprintf (dump_file, "optimizing double bit test to ");
	  print_generic_expr (dump_file, name1, 0);
	  fprintf (dump_file, " & T == T\nwith temporary T = (1 << ");
	  print_generic_expr (dump_file, bit1, 0);
	  fprintf (dump_file, ") | (1 << ");
	  print_generic_expr (dump_file, bit2, 0);
	  fprintf (dump_file, ")\n");
	}

      return true;
    }


  else if (TREE_CODE_CLASS (gimple_cond_code (inner_cond)) == tcc_comparison
	   && TREE_CODE_CLASS (gimple_cond_code (outer_cond)) == tcc_comparison)
    {
      tree t;

      if (!(t = maybe_fold_and_comparisons (gimple_cond_code (inner_cond),
					    gimple_cond_lhs (inner_cond),
					    gimple_cond_rhs (inner_cond),
					    gimple_cond_code (outer_cond),
					    gimple_cond_lhs (outer_cond),
					    gimple_cond_rhs (outer_cond))))
	return false;
      t = canonicalize_cond_expr_cond (t);
      if (!t)
	return false;
      gimple_cond_set_condition_from_tree (inner_cond, t);
      update_stmt (inner_cond);


      gimple_cond_set_condition_from_tree (outer_cond, boolean_true_node);
      update_stmt (outer_cond);

      if (dump_file)
	{
	  fprintf (dump_file, "optimizing two comparisons to ");
	  print_generic_expr (dump_file, t, 0);
	  fprintf (dump_file, "\n");
	}

      return true;
    }

  return false;
}
