restore_fixed_argument_area (rtx save_area, rtx argblock, int high_to_save, int low_to_save)
{
  enum machine_mode save_mode = GET_MODE (save_area);
  int delta;
  rtx addr, stack_area;

#ifdef ARGS_GROW_DOWNWARD
  delta = -high_to_save;
#else
  delta = low_to_save;
#endif
  addr = plus_constant (Pmode, argblock, delta);
  stack_area = gen_rtx_MEM (save_mode, memory_address (save_mode, addr));
  set_mem_align (stack_area, PARM_BOUNDARY);

  if (save_mode != BLKmode)
    emit_move_insn (stack_area, save_area);
  else
    emit_block_move (stack_area, validize_mem (save_area),
		     GEN_INT (high_to_save - low_to_save + 1),
		     BLOCK_OP_CALL_PARM);
}
