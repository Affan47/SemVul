find_defs (struct loop *loop, basic_block *body)
{
  unsigned i;
  bitmap blocks = BITMAP_ALLOC (NULL);

  for (i = 0; i < loop->num_nodes; i++)
    bitmap_set_bit (blocks, body[i]->index);

  df_remove_problem (df_chain);
  df_process_deferred_rescans ();
  df_chain_add_problem (DF_UD_CHAIN);
  df_set_blocks (blocks);
  df_analyze ();

  if (dump_file)
    {
      df_dump_region (dump_file);
      fprintf (dump_file, "*****starting processing of loop  ******\n");
      print_rtl_with_bb (dump_file, get_insns ());
      fprintf (dump_file, "*****ending processing of loop  ******\n");
    }
  check_invariant_table_size ();

  BITMAP_FREE (blocks);
}
