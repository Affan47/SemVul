df_ref_change_reg_with_loc_1 (struct df_reg_info *old_df,
			      struct df_reg_info *new_df,
			      int new_regno, rtx loc)
{
  df_ref the_ref = old_df->reg_chain;

  while (the_ref)
    {
      if ((!DF_REF_IS_ARTIFICIAL (the_ref))
	  && DF_REF_LOC (the_ref)
	  && (*DF_REF_LOC (the_ref) == loc))
	{
	  df_ref next_ref = DF_REF_NEXT_REG (the_ref);
	  df_ref prev_ref = DF_REF_PREV_REG (the_ref);
	  df_ref *ref_vec, *ref_vec_t;
	  struct df_insn_info *insn_info = DF_REF_INSN_INFO (the_ref);
	  unsigned int count = 0;

	  DF_REF_REGNO (the_ref) = new_regno;
	  DF_REF_REG (the_ref) = regno_reg_rtx[new_regno];


	  if (prev_ref)
	    DF_REF_NEXT_REG (prev_ref) = next_ref;
	  else
	    old_df->reg_chain = next_ref;
	  if (next_ref)
	    DF_REF_PREV_REG (next_ref) = prev_ref;
	  old_df->n_refs--;


	  DF_REF_PREV_REG (the_ref) = NULL;
	  DF_REF_NEXT_REG (the_ref) = new_df->reg_chain;
	  if (new_df->reg_chain)
	    DF_REF_PREV_REG (new_df->reg_chain) = the_ref;
	  new_df->reg_chain = the_ref;
	  new_df->n_refs++;
	  if (DF_REF_BB (the_ref))
	    df_set_bb_dirty (DF_REF_BB (the_ref));


	  if (DF_REF_FLAGS (the_ref) & DF_REF_IN_NOTE)
	    ref_vec = insn_info->eq_uses;
	  else
	    ref_vec = insn_info->uses;
	  if (dump_file)
	    fprintf (dump_file, "changing reg in insn %d\n",
		     DF_REF_INSN_UID (the_ref));

	  ref_vec_t = ref_vec;


	  while (*ref_vec_t)
	    {
	      count++;
	      ref_vec_t++;
	    }
	  qsort (ref_vec, count, sizeof (df_ref ), df_ref_compare);

	  the_ref = next_ref;
	}
      else
	the_ref = DF_REF_NEXT_REG (the_ref);
    }
}
