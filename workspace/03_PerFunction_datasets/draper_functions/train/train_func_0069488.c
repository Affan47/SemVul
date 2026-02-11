find_interesting_uses (struct ivopts_data *data)
{
  basic_block bb;
  gimple_stmt_iterator bsi;
  basic_block *body = get_loop_body (data->current_loop);
  unsigned i;
  struct version_info *info;
  edge e;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Uses:\n\n");

  for (i = 0; i < data->current_loop->num_nodes; i++)
    {
      edge_iterator ei;
      bb = body[i];

      FOR_EACH_EDGE (e, ei, bb->succs)
	if (e->dest != EXIT_BLOCK_PTR
	    && !flow_bb_inside_loop_p (data->current_loop, e->dest))
	  find_interesting_uses_outside (data, e);

      for (bsi = gsi_start_phis (bb); !gsi_end_p (bsi); gsi_next (&bsi))
	find_interesting_uses_stmt (data, gsi_stmt (bsi));
      for (bsi = gsi_start_bb (bb); !gsi_end_p (bsi); gsi_next (&bsi))
	if (!is_gimple_debug (gsi_stmt (bsi)))
	  find_interesting_uses_stmt (data, gsi_stmt (bsi));
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      bitmap_iterator bi;

      fprintf (dump_file, "\n");

      EXECUTE_IF_SET_IN_BITMAP (data->relevant, 0, i, bi)
	{
	  info = ver_info (data, i);
	  if (info->inv_id)
	    {
	      fprintf (dump_file, "  ");
	      print_generic_expr (dump_file, info->name, TDF_SLIM);
	      fprintf (dump_file, " is invariant (%d)%s\n",
		       info->inv_id, info->has_nonlin_use ? "" : ", eliminable");
	    }
	}

      fprintf (dump_file, "\n");
    }

  free (body);
}
