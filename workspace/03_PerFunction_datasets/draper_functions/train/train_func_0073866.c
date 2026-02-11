dse_step2_init (void)
{
  unsigned int i;
  group_info_t group;

  FOR_EACH_VEC_ELT (rtx_group_vec, i, group)
    {


      if (stores_off_frame_dead_at_return && group->frame_related)
	{
	  bitmap_ior_into (group->store2_n, group->store1_n);
	  bitmap_ior_into (group->store2_p, group->store1_p);
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "group %d is frame related ", i);
	}

      group->offset_map_size_n++;
      group->offset_map_n = XOBNEWVEC (&dse_obstack, int,
				       group->offset_map_size_n);
      group->offset_map_size_p++;
      group->offset_map_p = XOBNEWVEC (&dse_obstack, int,
				       group->offset_map_size_p);
      group->process_globally = false;
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "group %d(%d+%d): ", i,
		   (int)bitmap_count_bits (group->store2_n),
		   (int)bitmap_count_bits (group->store2_p));
	  bitmap_print (dump_file, group->store2_n, "n ", " ");
	  bitmap_print (dump_file, group->store2_p, "p ", "\n");
	}
    }
}
