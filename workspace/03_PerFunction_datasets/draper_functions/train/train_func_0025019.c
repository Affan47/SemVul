make_blocks (gimple_seq seq)
{
  gimple_stmt_iterator i = gsi_start (seq);
  gimple stmt = NULL;
  bool start_new_block = true;
  bool first_stmt_of_seq = true;
  basic_block bb = ENTRY_BLOCK_PTR;

  while (!gsi_end_p (i))
    {
      gimple prev_stmt;

      prev_stmt = stmt;
      stmt = gsi_stmt (i);


      if (start_new_block || stmt_starts_bb_p (stmt, prev_stmt))
	{
	  if (!first_stmt_of_seq)
	    gsi_split_seq_before (&i, &seq);
	  bb = create_basic_block (seq, NULL, bb);
	  start_new_block = false;
	}


      gimple_set_bb (stmt, bb);

      if (computed_goto_p (stmt))
	found_computed_goto = true;


      if (stmt_ends_bb_p (stmt))
	{


	  if (gimple_has_lhs (stmt)
	      && stmt_can_make_abnormal_goto (stmt)
	      && is_gimple_reg_type (TREE_TYPE (gimple_get_lhs (stmt))))
	    {
	      tree lhs = gimple_get_lhs (stmt);
	      tree tmp = create_tmp_var (TREE_TYPE (lhs), NULL);
	      gimple s = gimple_build_assign (lhs, tmp);
	      gimple_set_location (s, gimple_location (stmt));
	      gimple_set_block (s, gimple_block (stmt));
	      gimple_set_lhs (stmt, tmp);
	      if (TREE_CODE (TREE_TYPE (tmp)) == COMPLEX_TYPE
		  || TREE_CODE (TREE_TYPE (tmp)) == VECTOR_TYPE)
		DECL_GIMPLE_REG_P (tmp) = 1;
	      gsi_insert_after (&i, s, GSI_SAME_STMT);
	    }
	  start_new_block = true;
	}

      gsi_next (&i);
      first_stmt_of_seq = false;
    }
}
