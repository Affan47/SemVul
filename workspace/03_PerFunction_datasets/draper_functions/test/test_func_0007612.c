xtensa_create_property_segments (frag_predicate property_function,
				 frag_predicate end_property_function,
				 const char *section_name_base,
				 xt_section_type sec_type)
{
  segT *seclist;


  for (seclist = &stdoutput->sections;
       seclist && *seclist;
       seclist = &(*seclist)->next)
    {
      segT sec = *seclist;

      if (exclude_section_from_property_tables (sec))
	continue;

      if (section_has_property (sec, property_function))
	{
	  segment_info_type *xt_seg_info;
	  xtensa_block_info **xt_blocks;
	  segT prop_sec = xtensa_make_property_section (sec, section_name_base);

	  prop_sec->output_section = prop_sec;
	  subseg_set (prop_sec, 0);
	  xt_seg_info = seg_info (prop_sec);
	  xt_blocks = &xt_seg_info->tc_segment_info_data.blocks[sec_type];


	  add_xt_block_frags (sec, xt_blocks, property_function,
			      end_property_function);
	}
    }


  for (seclist = &stdoutput->sections;
       seclist && *seclist;
       seclist = &(*seclist)->next)
    {
      segment_info_type *seginfo;
      xtensa_block_info *block;
      segT sec = *seclist;

      seginfo = seg_info (sec);
      block = seginfo->tc_segment_info_data.blocks[sec_type];

      if (block)
	{
	  xtensa_block_info *cur_block;
	  int num_recs = 0;
	  bfd_size_type rec_size;

	  for (cur_block = block; cur_block; cur_block = cur_block->next)
	    num_recs++;

	  rec_size = num_recs * 8;
	  bfd_set_section_size (stdoutput, sec, rec_size);

	  if (num_recs)
	    {
	      char *frag_data;
	      int i;

	      subseg_set (sec, 0);
	      frag_data = frag_more (rec_size);
	      cur_block = block;
	      for (i = 0; i < num_recs; i++)
		{
		  fixS *fix;


		  gas_assert (cur_block);
		  fix = fix_new (frag_now, i * 8, 4,
				 section_symbol (cur_block->sec),
				 cur_block->offset,
				 FALSE, BFD_RELOC_32);
		  fix->fx_file = "<internal>";
		  fix->fx_line = 0;


		  md_number_to_chars (&frag_data[4 + i * 8],
				      cur_block->size, 4);
		  cur_block = cur_block->next;
		}
	      frag_wane (frag_now);
	      frag_new (0);
	      frag_wane (frag_now);
	    }
	}
    }
}
