df_md_bb_local_compute_process_def (struct df_md_bb_info *bb_info,
                                    df_ref *def_rec,
                                    int top_flag)
{
  df_ref def;
  bitmap_clear (&seen_in_insn);

  while ((def = *def_rec++) != NULL)
    {
      unsigned int dregno = DF_REF_REGNO (def);
      if (((!(df->changeable_flags & DF_NO_HARD_REGS))
	    || (dregno >= FIRST_PSEUDO_REGISTER))
	  && top_flag == (DF_REF_FLAGS (def) & DF_REF_AT_TOP))
	{
          if (!bitmap_bit_p (&seen_in_insn, dregno))
	    {
	      if (DF_REF_FLAGS (def)
	          & (DF_REF_PARTIAL | DF_REF_CONDITIONAL | DF_REF_MAY_CLOBBER))
	        {
	          bitmap_set_bit (&bb_info->gen, dregno);
	          bitmap_clear_bit (&bb_info->kill, dregno);
	        }
	      else
	        {


	          bitmap_set_bit (&seen_in_insn, dregno);
	          bitmap_set_bit (&bb_info->kill, dregno);
	          bitmap_clear_bit (&bb_info->gen, dregno);
	        }
	    }
	}
    }
}
