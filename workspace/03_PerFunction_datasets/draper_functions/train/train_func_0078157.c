mf_xform_statements (void)
{
  basic_block bb, next;
  gimple_stmt_iterator i;
  int saved_last_basic_block = last_basic_block;
  enum gimple_rhs_class grhs_class;

  bb = ENTRY_BLOCK_PTR ->next_bb;
  do
    {
      next = bb->next_bb;
      for (i = gsi_start_bb (bb); !gsi_end_p (i); gsi_next (&i))
        {
          gimple s = gsi_stmt (i);


          switch (gimple_code (s))
            {
            case GIMPLE_ASSIGN:
	      mf_xform_derefs_1 (&i, gimple_assign_lhs_ptr (s),
		  		 gimple_location (s), integer_one_node);
	      mf_xform_derefs_1 (&i, gimple_assign_rhs1_ptr (s),
		  		 gimple_location (s), integer_zero_node);
	      grhs_class = get_gimple_rhs_class (gimple_assign_rhs_code (s));
	      if (grhs_class == GIMPLE_BINARY_RHS)
		mf_xform_derefs_1 (&i, gimple_assign_rhs2_ptr (s),
				   gimple_location (s), integer_zero_node);
              break;

            case GIMPLE_RETURN:
              if (gimple_return_retval (s) != NULL_TREE)
                {
                  mf_xform_derefs_1 (&i, gimple_return_retval_ptr (s),
				     gimple_location (s),
				     integer_zero_node);
                }
              break;

            default:
              ;
            }
        }
      bb = next;
    }
  while (bb && bb->index <= saved_last_basic_block);
}
