setup_regno_cost_classes_by_aclass (int regno, enum reg_class aclass)
{
  static struct cost_classes classes;
  cost_classes_t classes_ptr;
  enum reg_class cl;
  int i;
  PTR *slot;
  HARD_REG_SET temp, temp2;
  bool exclude_p;

  if ((classes_ptr = cost_classes_aclass_cache[aclass]) == NULL)
    {
      COPY_HARD_REG_SET (temp, reg_class_contents[aclass]);
      AND_COMPL_HARD_REG_SET (temp, ira_no_alloc_regs);


      for (i = 0; i < ira_pressure_classes_num; i++)
	{
	  cl = ira_pressure_classes[i];
	  if (cl == aclass)
	    break;
	  COPY_HARD_REG_SET (temp2, reg_class_contents[cl]);
	  AND_COMPL_HARD_REG_SET (temp2, ira_no_alloc_regs);
	  if (hard_reg_set_subset_p (temp, temp2))
	    break;
	}
      exclude_p = i < ira_pressure_classes_num;
      classes.num = 0;
      for (i = 0; i < ira_important_classes_num; i++)
	{
	  cl = ira_important_classes[i];
	  if (exclude_p)
	    {


	      COPY_HARD_REG_SET (temp2, reg_class_contents[cl]);
	      AND_COMPL_HARD_REG_SET (temp2, ira_no_alloc_regs);
	      if (! ira_reg_pressure_class_p[cl]
		  && hard_reg_set_subset_p (temp2, temp) && cl != aclass)
		continue;
	    }
	  classes.classes[classes.num++] = cl;
	}
      slot = htab_find_slot (cost_classes_htab, &classes, INSERT);
      if (*slot == NULL)
	{
	  classes_ptr = setup_cost_classes (&classes);
	  *slot = classes_ptr;
	}
      classes_ptr = cost_classes_aclass_cache[aclass] = (cost_classes_t) *slot;
    }
  regno_cost_classes[regno] = classes_ptr;
}
