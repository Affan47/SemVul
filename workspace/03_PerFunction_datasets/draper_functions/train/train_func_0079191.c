convert_pinerc_filts_patterns(long int use_flags)
{
    long      old_rflags;
    long      rflags;
    PAT_S    *pat;
    PAT_STATE pstate;
    ACTION_S *act;

    old_rflags = (ROLE_OLD_FILT | use_flags);

    rflags = 0L;
    if(any_patterns(old_rflags, &pstate)){
	dprint((2, "converting old filter patterns to new (%s)\n", (use_flags == PAT_USE_MAIN) ? "Main" : "Post"));
	for(pat = first_pattern(&pstate);
	    pat;
	    pat = next_pattern(&pstate)){
	    if((act = pat->action) != NULL){
		if(act->is_a_filter &&
		   add_to_pattern(pat, ROLE_DO_FILTER | use_flags))
		  rflags |= ROLE_DO_FILTER;
	    }
	}

	if(rflags)
	  if(write_patterns(rflags | use_flags))
	    dprint((1,
		   "Trouble converting filter patterns to new variable\n"));
    }
}
