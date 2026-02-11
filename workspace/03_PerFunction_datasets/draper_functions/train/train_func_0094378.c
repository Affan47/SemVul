xtensa_find_unmarked_state_frags (void)
{
  segT *seclist;


  for (seclist = &stdoutput->sections;
       seclist && *seclist;
       seclist = &(*seclist)->next)
    {
      segT sec = *seclist;
      segment_info_type *seginfo;
      fragS *fragP;
      flagword flags;
      flags = bfd_get_section_flags (stdoutput, sec);
      if (flags & SEC_DEBUGGING)
	continue;
      if (!(flags & SEC_ALLOC))
	continue;

      seginfo = seg_info (sec);
      if (seginfo && seginfo->frchainP)
	{
	  fragS *last_fragP = 0;
	  for (fragP = seginfo->frchainP->frch_root; fragP;
	       fragP = fragP->fr_next)
	    {
	      if (fragP->fr_fix != 0
		  && !fragP->tc_frag_data.is_assembly_state_set)
		{
		  if (last_fragP == 0)
		    {
		      as_warn_where (fragP->fr_file, fragP->fr_line,
				     _("assembly state not set for first frag in section %s"),
				     sec->name);
		    }
		  else
		    {
		      fragP->tc_frag_data.is_assembly_state_set = TRUE;
		      fragP->tc_frag_data.is_no_density =
			last_fragP->tc_frag_data.is_no_density;
		      fragP->tc_frag_data.is_no_transform =
			last_fragP->tc_frag_data.is_no_transform;
		      fragP->tc_frag_data.use_longcalls =
			last_fragP->tc_frag_data.use_longcalls;
		      fragP->tc_frag_data.use_absolute_literals =
			last_fragP->tc_frag_data.use_absolute_literals;
		    }
		}
	      if (fragP->tc_frag_data.is_assembly_state_set)
		last_fragP = fragP;
	    }
	}
    }
}
