lower_sequence (gimple_seq seq, struct lower_data *data)
{
  gimple_stmt_iterator gsi;

  for (gsi = gsi_start (seq); !gsi_end_p (gsi); )
    lower_stmt (&gsi, data);
}
