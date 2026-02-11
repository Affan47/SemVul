setup_prohibited_class_mode_regs (void)
{
  int j, k, hard_regno, cl, last_hard_regno, count;

  for (cl = (int) N_REG_CLASSES - 1; cl >= 0; cl--)
    {
      COPY_HARD_REG_SET (temp_hard_regset, reg_class_contents[cl]);
      AND_COMPL_HARD_REG_SET (temp_hard_regset, no_unit_alloc_regs);
      for (j = 0; j < NUM_MACHINE_MODES; j++)
	{
	  count = 0;
	  last_hard_regno = -1;
	  CLEAR_HARD_REG_SET (ira_prohibited_class_mode_regs[cl][j]);
	  for (k = ira_class_hard_regs_num[cl] - 1; k >= 0; k--)
	    {
	      hard_regno = ira_class_hard_regs[cl][k];
	      if (! HARD_REGNO_MODE_OK (hard_regno, (enum machine_mode) j))
		SET_HARD_REG_BIT (ira_prohibited_class_mode_regs[cl][j],
				  hard_regno);
	      else if (in_hard_reg_set_p (temp_hard_regset,
					  (enum machine_mode) j, hard_regno))
		{
		  last_hard_regno = hard_regno;
		  count++;
		}
	    }
	  ira_class_singleton[cl][j] = (count == 1 ? last_hard_regno : -1);
	}
    }
}
