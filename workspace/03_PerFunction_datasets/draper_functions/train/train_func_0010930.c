setup_reg_class_nregs (void)
{
  int i, cl, cl2, m;

  for (m = 0; m < MAX_MACHINE_MODE; m++)
    {
      for (cl = 0; cl < N_REG_CLASSES; cl++)
	ira_reg_class_max_nregs[cl][m]
	  = ira_reg_class_min_nregs[cl][m]
	  = targetm.class_max_nregs ((reg_class_t) cl, (enum machine_mode) m);
      for (cl = 0; cl < N_REG_CLASSES; cl++)
	for (i = 0;
	     (cl2 = alloc_reg_class_subclasses[cl][i]) != LIM_REG_CLASSES;
	     i++)
	  if (ira_reg_class_min_nregs[cl2][m]
	      < ira_reg_class_min_nregs[cl][m])
	    ira_reg_class_min_nregs[cl][m] = ira_reg_class_min_nregs[cl2][m];
    }
}
