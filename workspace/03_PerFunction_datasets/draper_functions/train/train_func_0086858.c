df_rd_alloc (bitmap all_blocks)
{
  unsigned int bb_index;
  bitmap_iterator bi;
  struct df_rd_problem_data *problem_data;

  if (df_rd->problem_data)
    {
      problem_data = (struct df_rd_problem_data *) df_rd->problem_data;
      bitmap_clear (&problem_data->sparse_invalidated_by_call);
      bitmap_clear (&problem_data->dense_invalidated_by_call);
    }
  else
    {
      problem_data = XNEW (struct df_rd_problem_data);
      df_rd->problem_data = problem_data;

      bitmap_obstack_initialize (&problem_data->rd_bitmaps);
      bitmap_initialize (&problem_data->sparse_invalidated_by_call,
			 &problem_data->rd_bitmaps);
      bitmap_initialize (&problem_data->dense_invalidated_by_call,
			 &problem_data->rd_bitmaps);
    }

  df_grow_bb_info (df_rd);


  EXECUTE_IF_SET_IN_BITMAP (all_blocks, 0, bb_index, bi)
    {
      struct df_rd_bb_info *bb_info = df_rd_get_bb_info (bb_index);


      if (bb_info->kill.obstack)
	{
	  bitmap_clear (&bb_info->kill);
	  bitmap_clear (&bb_info->sparse_kill);
	  bitmap_clear (&bb_info->gen);
	}
      else
	{
	  bitmap_initialize (&bb_info->kill, &problem_data->rd_bitmaps);
	  bitmap_initialize (&bb_info->sparse_kill, &problem_data->rd_bitmaps);
	  bitmap_initialize (&bb_info->gen, &problem_data->rd_bitmaps);
	  bitmap_initialize (&bb_info->in, &problem_data->rd_bitmaps);
	  bitmap_initialize (&bb_info->out, &problem_data->rd_bitmaps);
	}
    }
  df_rd->optional_p = true;
}
