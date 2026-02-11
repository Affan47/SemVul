setup_save_areas (void)
{
  int i, j, k;
  unsigned int r;
  HARD_REG_SET hard_regs_used;


  CLEAR_HARD_REG_SET (hard_regs_used);
  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    if (reg_renumber[i] >= 0 && REG_N_CALLS_CROSSED (i) > 0)
      {
	unsigned int regno = reg_renumber[i];
	unsigned int endregno
	  = regno + HARD_REGNO_NREGS (regno, GET_MODE (regno_reg_rtx[i]));

	for (r = regno; r < endregno; r++)
	  if (call_used_regs[r])
	    SET_HARD_REG_BIT (hard_regs_used, r);
      }


  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = MOVE_MAX_WORDS; j > 0; j--)
      {
	int do_save = 1;


	if (regno_save_mode[i][j] == VOIDmode || regno_save_mem[i][1] != 0)
	  continue;


	for (k = 0; k < j; k++)
	  if (regno_save_mem[i + k][1])
	    {
	      do_save = 0;
	      break;
	    }
	if (! do_save)
	  continue;

	for (k = 0; k < j; k++)
	  if (! TEST_HARD_REG_BIT (hard_regs_used, i + k))
	    {
	      do_save = 0;
	      break;
	    }
	if (! do_save)
	  continue;


	regno_save_mem[i][j]
	  = assign_stack_local (regno_save_mode[i][j],
				GET_MODE_SIZE (regno_save_mode[i][j]), 0);


	for (k = 0; k < j; k++)


	  regno_save_mem[i + k][1]
	    = adjust_address_nv (regno_save_mem[i][j],
				 regno_save_mode[i + k][1],
				 k * UNITS_PER_WORD);
      }


  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = MOVE_MAX_WORDS; j > 0; j--)
      if (regno_save_mem[i][j] != 0)
	set_mem_alias_set (regno_save_mem[i][j], get_frame_alias_set ());
}
