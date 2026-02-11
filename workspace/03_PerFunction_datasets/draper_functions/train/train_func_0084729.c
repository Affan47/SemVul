relax_frag_for_align (fragS *fragP, long stretch)
{


  long stretch_me;
  long diff;

  gas_assert (fragP->fr_subtype == RELAX_FILL_NOP
	  || fragP->fr_subtype == RELAX_UNREACHABLE
	  || (fragP->fr_subtype == RELAX_SLOTS
	      && fragP->tc_frag_data.slot_subtypes[0] == RELAX_NARROW));

  stretch_me = future_alignment_required (fragP, stretch);
  diff = stretch_me - fragP->tc_frag_data.text_expansion[0];
  if (diff == 0)
    return 0;

  if (diff < 0)
    {

      long shrink = fragP->tc_frag_data.text_expansion[0] - stretch_me;
      if (shrink <= stretch && stretch > 0)
	{
	  fragP->tc_frag_data.text_expansion[0] = stretch_me;
	  return -shrink;
	}
      return 0;
    }


  fragP->tc_frag_data.text_expansion[0] = stretch_me;

  return diff;
}
