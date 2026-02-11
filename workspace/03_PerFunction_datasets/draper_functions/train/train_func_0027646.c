compute_ld_motion_mems (void)
{
  struct ls_expr * ptr;
  basic_block bb;
  rtx insn;

  pre_ldst_mems = NULL;
  pre_ldst_table
    = htab_create (13, pre_ldst_expr_hash, pre_ldst_expr_eq, NULL);

  FOR_EACH_BB (bb)
    {
      FOR_BB_INSNS (bb, insn)
	{
	  if (NONDEBUG_INSN_P (insn))
	    {
	      if (GET_CODE (PATTERN (insn)) == SET)
		{
		  rtx src = SET_SRC (PATTERN (insn));
		  rtx dest = SET_DEST (PATTERN (insn));


		  if (MEM_P (src) && simple_mem (src))
		    {
		      ptr = ldst_entry (src);
		      if (REG_P (dest))
			ptr->loads = alloc_INSN_LIST (insn, ptr->loads);
		      else
			ptr->invalid = 1;
		    }
		  else
		    {

		      invalidate_any_buried_refs (src);
		    }


		  if (MEM_P (dest) && simple_mem (dest))
		    {
		      ptr = ldst_entry (dest);

		      if (! MEM_P (src)
			  && GET_CODE (src) != ASM_OPERANDS


			  && can_assign_to_reg_without_clobbers_p (src))
			ptr->stores = alloc_INSN_LIST (insn, ptr->stores);
		      else
			ptr->invalid = 1;
		    }
		}
	      else
		invalidate_any_buried_refs (PATTERN (insn));
	    }
	}
    }
}
