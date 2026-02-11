xtensa_cleanup_align_frags (void)
{
  frchainS *frchP;
  asection *s;

  for (s = stdoutput->sections; s; s = s->next)
    for (frchP = seg_info (s)->frchainP; frchP; frchP = frchP->frch_next)
      {
	fragS *fragP;

	for (fragP = frchP->frch_root; fragP; fragP = fragP->fr_next)
	  {
	    if ((fragP->fr_type == rs_align
		 || fragP->fr_type == rs_align_code
		 || (fragP->fr_type == rs_machine_dependent
		     && (fragP->fr_subtype == RELAX_DESIRE_ALIGN
			 || fragP->fr_subtype == RELAX_DESIRE_ALIGN_IF_TARGET)))
		&& fragP->fr_fix == 0)
	      {
		fragS *next = fragP->fr_next;

		while (next
		       && next->fr_fix == 0
		       && next->fr_type == rs_machine_dependent
		       && next->fr_subtype == RELAX_DESIRE_ALIGN_IF_TARGET)
		  {
		    frag_wane (next);
		    next = next->fr_next;
		  }
	      }


	    if (fragP->tc_frag_data.is_branch_target
		&& fragP->fr_opcode == fragP->fr_literal
		&& fragP->fr_type == rs_machine_dependent
		&& fragP->fr_subtype == RELAX_SLOTS
		&& fragP->tc_frag_data.slot_subtypes[0] == RELAX_NARROW)
	      frag_wane (fragP);
	    if (fragP->fr_type == rs_machine_dependent
		&& fragP->fr_subtype == RELAX_UNREACHABLE)
	      fragP->tc_frag_data.is_unreachable = TRUE;
	  }
      }
}
