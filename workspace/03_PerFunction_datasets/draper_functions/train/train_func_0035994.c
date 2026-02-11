gimple_block_label (basic_block bb)
{
  gimple_stmt_iterator i, s = gsi_start_bb (bb);
  bool first = true;
  tree label;
  gimple stmt;

  for (i = s; !gsi_end_p (i); first = false, gsi_next (&i))
    {
      stmt = gsi_stmt (i);
      if (gimple_code (stmt) != GIMPLE_LABEL)
	break;
      label = gimple_label_label (stmt);
      if (!DECL_NONLOCAL (label))
	{
	  if (!first)
	    gsi_move_before (&i, &s);
	  return label;
	}
    }

  label = create_artificial_label (UNKNOWN_LOCATION);
  stmt = gimple_build_label (label);
  gsi_insert_before (&s, stmt, GSI_NEW_STMT);
  return label;
}
