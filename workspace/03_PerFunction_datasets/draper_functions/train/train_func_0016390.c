first_non_label_stmt (basic_block bb)
{
  gimple_stmt_iterator i = gsi_start_bb (bb);
  while (!gsi_end_p (i) && gimple_code (gsi_stmt (i)) == GIMPLE_LABEL)
    gsi_next (&i);
  return !gsi_end_p (i) ? gsi_stmt (i) : NULL;
}
