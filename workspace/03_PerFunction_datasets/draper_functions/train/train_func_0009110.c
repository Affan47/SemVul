model_excess_cost (rtx insn, bool print_p)
{
  int point, pci, cl, cost, this_cost, delta;
  struct reg_pressure_data *insn_reg_pressure;
  int insn_death[N_REG_CLASSES];

  calculate_reg_deaths (insn, insn_death);
  point = model_index (insn);
  insn_reg_pressure = INSN_REG_PRESSURE (insn);
  cost = 0;

  if (print_p)
    fprintf (sched_dump, ";;\t\t| %3d %4d | %4d %+3d |", point,
	     INSN_UID (insn), INSN_PRIORITY (insn), insn_delay (insn));


  for (pci = 0; pci < ira_pressure_classes_num; pci++)
    {
      cl = ira_pressure_classes[pci];
      delta = insn_reg_pressure[pci].set_increase - insn_death[cl];
      this_cost = model_excess_group_cost (&model_before_pressure,
					   point, pci, delta);
      cost += this_cost;
      if (print_p)
	fprintf (sched_dump, " %s:[%d base cost %d]",
		 reg_class_names[cl], delta, this_cost);
    }

  if (print_p)
    fprintf (sched_dump, "\n");

  return cost;
}
