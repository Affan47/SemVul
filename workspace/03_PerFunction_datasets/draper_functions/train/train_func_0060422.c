init_expr_target (void)
{
  rtx insn, pat;
  enum machine_mode mode;
  int num_clobbers;
  rtx mem, mem1;
  rtx reg;


  mem = gen_rtx_MEM (VOIDmode, stack_pointer_rtx);
  mem1 = gen_rtx_MEM (VOIDmode, frame_pointer_rtx);


  reg = gen_rtx_REG (VOIDmode, -1);

  insn = rtx_alloc (INSN);
  pat = gen_rtx_SET (VOIDmode, NULL_RTX, NULL_RTX);
  PATTERN (insn) = pat;

  for (mode = VOIDmode; (int) mode < NUM_MACHINE_MODES;
       mode = (enum machine_mode) ((int) mode + 1))
    {
      int regno;

      direct_load[(int) mode] = direct_store[(int) mode] = 0;
      PUT_MODE (mem, mode);
      PUT_MODE (mem1, mode);
      PUT_MODE (reg, mode);


      if (mode != VOIDmode && mode != BLKmode)
	for (regno = 0; regno < FIRST_PSEUDO_REGISTER
	     && (direct_load[(int) mode] == 0 || direct_store[(int) mode] == 0);
	     regno++)
	  {
	    if (! HARD_REGNO_MODE_OK (regno, mode))
	      continue;

	    SET_REGNO (reg, regno);

	    SET_SRC (pat) = mem;
	    SET_DEST (pat) = reg;
	    if (recog (pat, insn, &num_clobbers) >= 0)
	      direct_load[(int) mode] = 1;

	    SET_SRC (pat) = mem1;
	    SET_DEST (pat) = reg;
	    if (recog (pat, insn, &num_clobbers) >= 0)
	      direct_load[(int) mode] = 1;

	    SET_SRC (pat) = reg;
	    SET_DEST (pat) = mem;
	    if (recog (pat, insn, &num_clobbers) >= 0)
	      direct_store[(int) mode] = 1;

	    SET_SRC (pat) = reg;
	    SET_DEST (pat) = mem1;
	    if (recog (pat, insn, &num_clobbers) >= 0)
	      direct_store[(int) mode] = 1;
	  }
    }

  mem = gen_rtx_MEM (VOIDmode, gen_rtx_raw_REG (Pmode, 10000));

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_FLOAT); mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    {
      enum machine_mode srcmode;
      for (srcmode = GET_CLASS_NARROWEST_MODE (MODE_FLOAT); srcmode != mode;
	   srcmode = GET_MODE_WIDER_MODE (srcmode))
	{
	  enum insn_code ic;

	  ic = can_extend_p (mode, srcmode, 0);
	  if (ic == CODE_FOR_nothing)
	    continue;

	  PUT_MODE (mem, srcmode);

	  if (insn_operand_matches (ic, 1, mem))
	    float_extend_from_mem[mode][srcmode] = true;
	}
    }
}
