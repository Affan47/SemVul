bcma_pmu_get_cpu_clock(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53572)
		return 300000000;


	if (cc->pmu.rev >= 5) {
		u32 pll;
		switch (bus->chipinfo.id) {
		case BCMA_CHIP_ID_BCM4706:
			return bcma_pmu_pll_clock_bcm4706(cc,
						BCMA_CC_PMU4706_MAINPLL_PLL0,
						BCMA_CC_PMU5_MAINPLL_CPU);
		case BCMA_CHIP_ID_BCM5356:
			pll = BCMA_CC_PMU5356_MAINPLL_PLL0;
			break;
		case BCMA_CHIP_ID_BCM5357:
		case BCMA_CHIP_ID_BCM4749:
			pll = BCMA_CC_PMU5357_MAINPLL_PLL0;
			break;
		default:
			pll = BCMA_CC_PMU4716_MAINPLL_PLL0;
			break;
		}

		return bcma_pmu_pll_clock(cc, pll, BCMA_CC_PMU5_MAINPLL_CPU);
	}


	return bcma_pmu_get_bus_clock(cc);
}
