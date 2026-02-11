has_dependence_note_reg_clobber (int regno)
{
  struct deps_reg *reg_last = &has_dependence_data.dc->reg_last[regno];

  if (!sched_insns_conditions_mutex_p (has_dependence_data.pro,
				       VINSN_INSN_RTX
				       (has_dependence_data.con)))
    {
      ds_t *dsp = &has_dependence_data.has_dep_p[has_dependence_data.where];

      if (reg_last->sets)
	*dsp = (*dsp & ~SPECULATIVE) | DEP_OUTPUT;

      if (reg_last->uses)
	*dsp = (*dsp & ~SPECULATIVE) | DEP_ANTI;
    }
}
