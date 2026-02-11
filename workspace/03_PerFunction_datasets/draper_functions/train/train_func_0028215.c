df_get_call_refs (struct df_collection_rec * collection_rec,
                  basic_block bb,
                  struct df_insn_info *insn_info,
                  int flags)
{
  rtx note;
  bitmap_iterator bi;
  unsigned int ui;
  bool is_sibling_call;
  unsigned int i;
  df_ref def;
  bitmap_head defs_generated;

  bitmap_initialize (&defs_generated, &df_bitmap_obstack);


  FOR_EACH_VEC_ELT (df_ref, collection_rec->def_vec, i, def)
    bitmap_set_bit (&defs_generated, DF_REF_REGNO (def));


  for (note = CALL_INSN_FUNCTION_USAGE (insn_info->insn); note;
       note = XEXP (note, 1))
    {
      if (GET_CODE (XEXP (note, 0)) == USE)
        df_uses_record (collection_rec, &XEXP (XEXP (note, 0), 0),
			DF_REF_REG_USE, bb, insn_info, flags);
      else if (GET_CODE (XEXP (note, 0)) == CLOBBER)
	{
	  if (REG_P (XEXP (XEXP (note, 0), 0)))
	    {
	      unsigned int regno = REGNO (XEXP (XEXP (note, 0), 0));
	      if (!bitmap_bit_p (&defs_generated, regno))
		df_defs_record (collection_rec, XEXP (note, 0), bb,
				insn_info, flags);
	    }
	  else
	    df_uses_record (collection_rec, &XEXP (note, 0),
		            DF_REF_REG_USE, bb, insn_info, flags);
	}
    }


  df_ref_record (DF_REF_BASE, collection_rec, regno_reg_rtx[STACK_POINTER_REGNUM],
		 NULL, bb, insn_info, DF_REF_REG_USE,
		 DF_REF_CALL_STACK_USAGE | flags);


  if (!RTL_CONST_CALL_P (insn_info->insn))
    for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
      if (global_regs[i])
	{
	  df_ref_record (DF_REF_BASE, collection_rec, regno_reg_rtx[i],
			 NULL, bb, insn_info, DF_REF_REG_USE, flags);
	  if (!RTL_PURE_CALL_P (insn_info->insn))
	    df_ref_record (DF_REF_BASE, collection_rec, regno_reg_rtx[i],
			   NULL, bb, insn_info, DF_REF_REG_DEF, flags);
	}

  is_sibling_call = SIBLING_CALL_P (insn_info->insn);
  EXECUTE_IF_SET_IN_BITMAP (regs_invalidated_by_call_regset, 0, ui, bi)
    {
      if (!global_regs[ui]
	  && (!bitmap_bit_p (&defs_generated, ui))
	  && (!is_sibling_call
	      || !bitmap_bit_p (df->exit_block_uses, ui)
	      || refers_to_regno_p (ui, ui+1,
				    crtl->return_rtx, NULL)))
        df_ref_record (DF_REF_BASE, collection_rec, regno_reg_rtx[ui],
		       NULL, bb, insn_info, DF_REF_REG_DEF,
		       DF_REF_MAY_CLOBBER | flags);
    }

  bitmap_clear (&defs_generated);
  return;
}
