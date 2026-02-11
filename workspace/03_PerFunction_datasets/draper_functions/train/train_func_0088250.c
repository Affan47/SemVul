setup_hard_regno_aclass (void)
{
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
#if 1
      ira_hard_regno_allocno_class[i]
	= (TEST_HARD_REG_BIT (no_unit_alloc_regs, i)
	   ? NO_REGS
	   : ira_allocno_class_translate[REGNO_REG_CLASS (i)]);
#else
      int j;
      enum reg_class cl;
      ira_hard_regno_allocno_class[i] = NO_REGS;
      for (j = 0; j < ira_allocno_classes_num; j++)
 	{
	  cl = ira_allocno_classes[j];
 	  if (ira_class_hard_reg_index[cl][i] >= 0)
 	    {
	      ira_hard_regno_allocno_class[i] = cl;
 	      break;
 	    }
 	}
#endif
    }
}
