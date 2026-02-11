model_record_pressures (struct model_insn_info *insn)
{
  struct reg_pressure_data *reg_pressure;
  int point, pci, cl, delta;
  int death[N_REG_CLASSES];

  point = model_index (insn->insn);
  if (sched_verbose >= 2)
    {
      if (point == 0)
	{
	  fprintf (sched_dump, "\n;;\tModel schedule:\n;;\n");
	  fprintf (sched_dump, ";;\t| idx insn | mpri hght dpth prio |\n");
	}
      fprintf (sched_dump, ";;\t| %3d %4d | %4d %4d %4d %4d | %-30s ",
	       point, INSN_UID (insn->insn), insn->model_priority,
	       insn->depth + insn->alap, insn->depth,
	       INSN_PRIORITY (insn->insn),
	       str_pattern_slim (PATTERN (insn->insn)));
    }
  calculate_reg_deaths (insn->insn, death);
  reg_pressure = INSN_REG_PRESSURE (insn->insn);
  for (pci = 0; pci < ira_pressure_classes_num; pci++)
    {
      cl = ira_pressure_classes[pci];
      delta = reg_pressure[pci].set_increase - death[cl];
      if (sched_verbose >= 2)
	fprintf (sched_dump, " %s:[%d,%+d]", reg_class_names[cl],
		 curr_reg_pressure[cl], delta);
      model_record_pressure (&model_before_pressure, point, pci,
			     curr_reg_pressure[cl]);
    }
  if (sched_verbose >= 2)
    fprintf (sched_dump, "\n");
}
