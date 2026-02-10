entry_register (struct web_entry *entry, struct ref *ref, char *used,
                char *use_addressof)
{
  struct web_entry *root;
  rtx reg, newreg;


  root = unionfind_root (entry);
  if (root->reg)
    return root->reg;


  reg = DF_REF_REAL_REG (ref);


  if (!used[REGNO (reg)])
    newreg = reg, used[REGNO (reg)] = 1;
  else if (REG_USERVAR_P (reg) && 0)
    {
      newreg = reg;
      if (rtl_dump_file)
	fprintf (rtl_dump_file,
		 "New web forced to keep reg=%i (user variable)\n",
		 REGNO (reg));
    }
  else if (use_addressof [REGNO (reg)])
    {
      newreg = reg;
      if (rtl_dump_file)
	fprintf (rtl_dump_file,
		 "New web forced to keep reg=%i (address taken)\n",
		 REGNO (reg));
    }
  else
    {
      newreg = gen_reg_rtx (GET_MODE (reg));
      REG_USERVAR_P (newreg) = REG_USERVAR_P (reg);
      REG_POINTER (newreg) = REG_POINTER (reg);
      REG_LOOP_TEST_P (newreg) = REG_LOOP_TEST_P (reg);
      RTX_UNCHANGING_P (newreg) = RTX_UNCHANGING_P (reg);
      REG_ATTRS (newreg) = REG_ATTRS (reg);
      if (rtl_dump_file)
	fprintf (rtl_dump_file, "Web oldreg=%i newreg=%i\n", REGNO (reg),
		 REGNO (newreg));
    }

  root->reg = newreg;
  return newreg;
}
