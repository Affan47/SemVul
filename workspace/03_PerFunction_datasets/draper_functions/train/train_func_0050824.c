mark_regno_birth_or_death (int regno, bool birth_p)
{
  enum reg_class pressure_class;

  pressure_class = sched_regno_pressure_class[regno];
  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      if (pressure_class != NO_REGS)
	{
	  if (birth_p)
	    {
	      bitmap_set_bit (curr_reg_live, regno);
	      curr_reg_pressure[pressure_class]
		+= (ira_reg_class_max_nregs
		    [pressure_class][PSEUDO_REGNO_MODE (regno)]);
	    }
	  else
	    {
	      bitmap_clear_bit (curr_reg_live, regno);
	      curr_reg_pressure[pressure_class]
		-= (ira_reg_class_max_nregs
		    [pressure_class][PSEUDO_REGNO_MODE (regno)]);
	    }
	}
    }
  else if (pressure_class != NO_REGS
	   && ! TEST_HARD_REG_BIT (ira_no_alloc_regs, regno))
    {
      if (birth_p)
	{
	  bitmap_set_bit (curr_reg_live, regno);
	  curr_reg_pressure[pressure_class]++;
	}
      else
	{
	  bitmap_clear_bit (curr_reg_live, regno);
	  curr_reg_pressure[pressure_class]--;
	}
    }
}
