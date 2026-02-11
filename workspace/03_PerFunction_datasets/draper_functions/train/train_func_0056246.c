setup_class_subset_and_memory_move_costs (void)
{
  int cl, cl2, mode;
  HARD_REG_SET temp_hard_regset2;

  for (mode = 0; mode < MAX_MACHINE_MODE; mode++)
    ira_memory_move_cost[mode][NO_REGS][0]
      = ira_memory_move_cost[mode][NO_REGS][1] = SHRT_MAX;
  for (cl = (int) N_REG_CLASSES - 1; cl >= 0; cl--)
    {
      if (cl != (int) NO_REGS)
	for (mode = 0; mode < MAX_MACHINE_MODE; mode++)
	  {
	    ira_memory_move_cost[mode][cl][0] =
	      memory_move_cost ((enum machine_mode) mode,
				(enum reg_class) cl, false);
	    ira_memory_move_cost[mode][cl][1] =
	      memory_move_cost ((enum machine_mode) mode,
				(enum reg_class) cl, true);


	    if (ira_memory_move_cost[mode][NO_REGS][0]
		> ira_memory_move_cost[mode][cl][0])
	      ira_memory_move_cost[mode][NO_REGS][0]
		= ira_memory_move_cost[mode][cl][0];
	    if (ira_memory_move_cost[mode][NO_REGS][1]
		> ira_memory_move_cost[mode][cl][1])
	      ira_memory_move_cost[mode][NO_REGS][1]
		= ira_memory_move_cost[mode][cl][1];
	  }
      for (cl2 = (int) N_REG_CLASSES - 1; cl2 >= 0; cl2--)
	{
	  COPY_HARD_REG_SET (temp_hard_regset, reg_class_contents[cl]);
	  AND_COMPL_HARD_REG_SET (temp_hard_regset, no_unit_alloc_regs);
	  COPY_HARD_REG_SET (temp_hard_regset2, reg_class_contents[cl2]);
	  AND_COMPL_HARD_REG_SET (temp_hard_regset2, no_unit_alloc_regs);
	  ira_class_subset_p[cl][cl2]
	    = hard_reg_set_subset_p (temp_hard_regset, temp_hard_regset2);
	}
    }
}
