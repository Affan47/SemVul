tree_num_loop_insns (struct loop *loop, eni_weights *weights)
{
  basic_block *body = get_loop_body (loop);
  gimple_stmt_iterator gsi;
  unsigned size = 0, i;

  for (i = 0; i < loop->num_nodes; i++)
    for (gsi = gsi_start_bb (body[i]); !gsi_end_p (gsi); gsi_next (&gsi))
      size += estimate_num_insns (gsi_stmt (gsi), weights);
  free (body);

  return size;
}
