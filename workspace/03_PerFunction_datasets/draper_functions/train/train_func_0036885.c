initialize_uninitialized_subregs (void)
{
  rtx insn;
  edge e;
  int reg, did_something = 0;
  find_regno_partial_param param;

  for (e = ENTRY_BLOCK_PTR->succ; e; e = e->succ_next)
    {
      basic_block bb = e->dest;
      regset map = bb->global_live_at_start;
      EXECUTE_IF_SET_IN_REG_SET (map,
				 FIRST_PSEUDO_REGISTER, reg,
	{
	  int uid = REGNO_FIRST_UID (reg);
	  rtx i;


	  for (i = get_insns (); i && INSN_UID (i) != uid; i = NEXT_INSN (i))
	    ;
	  if (i != NULL_RTX)
	    {

	      param.regno_to_find = reg;
	      for_each_rtx (&i, find_regno_partial, &param);
	      if (param.retval != NULL_RTX)
		{
		  start_sequence ();
		  emit_move_insn (param.retval,
				  CONST0_RTX (GET_MODE (param.retval)));
		  insn = get_insns ();
		  end_sequence ();
		  insert_insn_on_edge (insn, e);
		  did_something = 1;
		}
	    }
	});
    }

  if (did_something)
    commit_edge_insertions ();
  return did_something;
}
