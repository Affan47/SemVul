find_retval (basic_block return_bb)
{
  gimple_stmt_iterator bsi;
  for (bsi = gsi_start_bb (return_bb); !gsi_end_p (bsi); gsi_next (&bsi))
    if (gimple_code (gsi_stmt (bsi)) == GIMPLE_RETURN)
      return gimple_return_retval (gsi_stmt (bsi));
    else if (gimple_code (gsi_stmt (bsi)) == GIMPLE_ASSIGN
	     && !gimple_clobber_p (gsi_stmt (bsi)))
      return gimple_assign_rhs1 (gsi_stmt (bsi));
  return NULL;
}
