init_resource_info (epilogue_insn)
     rtx epilogue_insn;
{
  int i;


  end_of_function_needs.cc = 0;
  end_of_function_needs.memory = 1;
  end_of_function_needs.unch_memory = 0;
  CLEAR_HARD_REG_SET (end_of_function_needs.regs);

  if (frame_pointer_needed)
    {
      SET_HARD_REG_BIT (end_of_function_needs.regs, FRAME_POINTER_REGNUM);
#if HARD_FRAME_POINTER_REGNUM != FRAME_POINTER_REGNUM
      SET_HARD_REG_BIT (end_of_function_needs.regs, HARD_FRAME_POINTER_REGNUM);
#endif
#ifdef EXIT_IGNORE_STACK
      if (! EXIT_IGNORE_STACK
	  || current_function_sp_is_unchanging)
#endif
	SET_HARD_REG_BIT (end_of_function_needs.regs, STACK_POINTER_REGNUM);
    }
  else
    SET_HARD_REG_BIT (end_of_function_needs.regs, STACK_POINTER_REGNUM);

  if (current_function_return_rtx != 0)
    mark_referenced_resources (current_function_return_rtx,
			       &end_of_function_needs, 1);

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if (global_regs[i]
#ifdef EPILOGUE_USES
	|| EPILOGUE_USES (i)
#endif
	)
      SET_HARD_REG_BIT (end_of_function_needs.regs, i);


  start_of_epilogue_needs = end_of_function_needs;

  while ((epilogue_insn = next_nonnote_insn (epilogue_insn)))
    mark_set_resources (epilogue_insn, &end_of_function_needs, 0,
			MARK_SRC_DEST_CALL);


  target_hash_table = (struct target_info **)
    xcalloc (TARGET_HASH_PRIME, sizeof (struct target_info *));
  bb_ticks = (int *) xcalloc (last_basic_block, sizeof (int));
}
