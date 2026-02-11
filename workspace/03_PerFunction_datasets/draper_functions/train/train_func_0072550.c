__intel_pmu_lbr_enable(bool pmi)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 debugctl, lbr_select = 0, orig_debugctl;


	if (pmi && x86_pmu.version >= 4)
		return;


	if (cpuc->lbr_sel)
		lbr_select = cpuc->lbr_sel->config;
	if (!pmi && cpuc->lbr_sel)
		wrmsrl(MSR_LBR_SELECT, lbr_select);

	rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	orig_debugctl = debugctl;
	debugctl |= DEBUGCTLMSR_LBR;


	if (!(lbr_select & LBR_CALL_STACK))
		debugctl |= DEBUGCTLMSR_FREEZE_LBRS_ON_PMI;
	if (orig_debugctl != debugctl)
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
}
