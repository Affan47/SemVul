reprogram_counter(struct kvm_pmu *pmu, int pmc_idx)
{
	struct kvm_pmc *pmc = kvm_x86_ops->pmu_ops->pmc_idx_to_pmc(pmu, pmc_idx);

	if (!pmc)
		return;

	if (pmc_is_gp(pmc))
		reprogram_gp_counter(pmc, pmc->eventsel);
	else {
		int idx = pmc_idx - INTEL_PMC_IDX_FIXED;
		u8 ctrl = fixed_ctrl_field(pmu->fixed_ctr_ctrl, idx);

		reprogram_fixed_counter(pmc, ctrl, idx);
	}
}
