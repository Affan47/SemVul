setup_preferred_alternate_classes_for_new_pseudos (int start)
{
  int i, old_regno;
  int max_regno = max_reg_num ();

  for (i = start; i < max_regno; i++)
    {
      old_regno = ORIGINAL_REGNO (regno_reg_rtx[i]);
      ira_assert (i != old_regno);
      setup_reg_classes (i, reg_preferred_class (old_regno),
			 reg_alternate_class (old_regno),
			 reg_allocno_class (old_regno));
      if (internal_flag_ira_verbose > 2 && ira_dump_file != NULL)
	fprintf (ira_dump_file,
		 "    New r%d: setting preferred %s, alternative %s\n",
		 i, reg_class_names[reg_preferred_class (old_regno)],
		 reg_class_names[reg_alternate_class (old_regno)]);
    }
}
