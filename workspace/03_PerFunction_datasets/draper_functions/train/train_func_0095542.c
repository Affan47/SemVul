bcma_pmu_init(struct bcma_drv_cc *cc)
{
	if (cc->pmu.rev == 1)
		bcma_cc_mask32(cc, BCMA_CC_PMU_CTL,
			      ~BCMA_CC_PMU_CTL_NOILPONW);
	else
		bcma_cc_set32(cc, BCMA_CC_PMU_CTL,
			     BCMA_CC_PMU_CTL_NOILPONW);

	bcma_pmu_pll_init(cc);
	bcma_pmu_resources_init(cc);
	bcma_pmu_workarounds(cc);
}
