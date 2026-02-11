xtensa_fix_a0_b_retw_frags (void)
{
  frchainS *frchP;
  asection *s;


  for (s = stdoutput->sections; s; s = s->next)
    for (frchP = seg_info (s)->frchainP; frchP; frchP = frchP->frch_next)
      {
	fragS *fragP;


	for (fragP = frchP->frch_root; fragP; fragP = fragP->fr_next)
	  {
	    if (fragP->fr_type == rs_machine_dependent
		&& fragP->fr_subtype == RELAX_ADD_NOP_IF_A0_B_RETW)
	      {
		if (next_instrs_are_b_retw (fragP))
		  {
		    if (fragP->tc_frag_data.is_no_transform)
		      as_bad (_("instruction sequence (write a0, branch, retw) may trigger hardware errata"));
		    else
		      relax_frag_add_nop (fragP);
		  }
		frag_wane (fragP);
	      }
	  }
      }
}
