bcma_pmu_get_bus_clock(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU4716_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM5356:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU5356_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU5357_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM4706:
		return bcma_pmu_pll_clock_bcm4706(cc,
						  BCMA_CC_PMU4706_MAINPLL_PLL0,
						  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM53572:
		return 75000000;
	default:
		bcma_warn(bus, "No bus clock specified for %04X device, pmu rev. %d, using default %d Hz\n",
			  bus->chipinfo.id, cc->pmu.rev, BCMA_CC_PMU_HT_CLOCK);
	}
	return BCMA_CC_PMU_HT_CLOCK;
}
