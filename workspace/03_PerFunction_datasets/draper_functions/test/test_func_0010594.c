setup_prohibited_mode_move_regs (void)
{
  int i, j;
  rtx test_reg1, test_reg2, move_pat, move_insn;

  if (ira_prohibited_mode_move_regs_initialized_p)
    return;
  ira_prohibited_mode_move_regs_initialized_p = true;
  test_reg1 = gen_rtx_REG (VOIDmode, 0);
  test_reg2 = gen_rtx_REG (VOIDmode, 0);
  move_pat = gen_rtx_SET (VOIDmode, test_reg1, test_reg2);
  move_insn = gen_rtx_INSN (VOIDmode, 0, 0, 0, 0, move_pat, 0, -1, 0);
  for (i = 0; i < NUM_MACHINE_MODES; i++)
    {
      SET_HARD_REG_SET (ira_prohibited_mode_move_regs[i]);
      for (j = 0; j < FIRST_PSEUDO_REGISTER; j++)
	{
	  if (! HARD_REGNO_MODE_OK (j, (enum machine_mode) i))
	    continue;
	  SET_REGNO_RAW (test_reg1, j);
	  PUT_MODE (test_reg1, (enum machine_mode) i);
	  SET_REGNO_RAW (test_reg2, j);
	  PUT_MODE (test_reg2, (enum machine_mode) i);
	  INSN_CODE (move_insn) = -1;
	  recog_memoized (move_insn);
	  if (INSN_CODE (move_insn) < 0)
	    continue;
	  extract_insn (move_insn);
	  if (! constrain_operands (1))
	    continue;
	  CLEAR_HARD_REG_BIT (ira_prohibited_mode_move_regs[i], j);
	}
    }
}
