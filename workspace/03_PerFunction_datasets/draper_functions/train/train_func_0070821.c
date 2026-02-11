lra_setup_reg_renumber (int regno, int hard_regno, bool print_p)
{
  int i, hr;


  lra_assert (hard_regno < 0 || reg_renumber[regno] < 0);
  if ((hr = hard_regno) < 0)
    hr = reg_renumber[regno];
  reg_renumber[regno] = hard_regno;
  lra_assert (hr >= 0);
  for (i = 0; i < hard_regno_nregs[hr][PSEUDO_REGNO_MODE (regno)]; i++)
    if (hard_regno < 0)
      lra_hard_reg_usage[hr + i] -= lra_reg_info[regno].freq;
    else
      lra_hard_reg_usage[hr + i] += lra_reg_info[regno].freq;
  if (print_p && lra_dump_file != NULL)
    fprintf (lra_dump_file, "	   Assign %d to %sr%d (freq=%d)\n",
	     reg_renumber[regno],
	     regno < lra_constraint_new_regno_start
	     ? ""
	     : bitmap_bit_p (&lra_inheritance_pseudos, regno) ? "inheritance "
	     : bitmap_bit_p (&lra_split_regs, regno) ? "split "
	     : bitmap_bit_p (&lra_optional_reload_pseudos, regno)
	     ? "optional reload ": "reload ",
	     regno, lra_reg_info[regno].freq);
  if (hard_regno >= 0)
    {
      curr_update_hard_regno_preference_check++;
      update_hard_regno_preference (regno, hard_regno, 1);
    }
}
