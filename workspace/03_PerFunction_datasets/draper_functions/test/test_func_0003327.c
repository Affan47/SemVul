section_has_xproperty (segT sec, frag_flags_fn property_function)
{
  segment_info_type *seginfo = seg_info (sec);
  fragS *fragP;

  if (seginfo && seginfo->frchainP)
    {
      for (fragP = seginfo->frchainP->frch_root; fragP; fragP = fragP->fr_next)
	{
	  frag_flags prop_flags;
	  property_function (fragP, &prop_flags);
	  if (!xtensa_frag_flags_is_empty (&prop_flags))
	    return TRUE;
	}
    }
  return FALSE;
}
