find_loop_location (struct loop *loop)
{
  gimple stmt = NULL;
  basic_block bb;
  gimple_stmt_iterator si;

  if (!loop)
    return UNKNOWN_LOC;

  stmt = get_loop_exit_condition (loop);

  if (stmt && gimple_location (stmt) != UNKNOWN_LOC)
    return gimple_location (stmt);


  if (!loop->header)
    return UNKNOWN_LOC;

  bb = loop->header;

  for (si = gsi_start_bb (bb); !gsi_end_p (si); gsi_next (&si))
    {
      stmt = gsi_stmt (si);
      if (gimple_location (stmt) != UNKNOWN_LOC)
        return gimple_location (stmt);
    }

  return UNKNOWN_LOC;
}
