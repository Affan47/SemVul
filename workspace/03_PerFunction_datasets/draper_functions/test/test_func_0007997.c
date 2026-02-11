bcma_pmu_resources_init(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;
	u32 min_msk = 0, max_msk = 0;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		min_msk = 0x200D;
		max_msk = 0xFFFF;
		break;
	case BCMA_CHIP_ID_BCM43142:
		min_msk = BCMA_RES_4314_LPLDO_PU |
			  BCMA_RES_4314_PMU_SLEEP_DIS |
			  BCMA_RES_4314_PMU_BG_PU |
			  BCMA_RES_4314_CBUCK_LPOM_PU |
			  BCMA_RES_4314_CBUCK_PFM_PU |
			  BCMA_RES_4314_CLDO_PU |
			  BCMA_RES_4314_LPLDO2_LVM |
			  BCMA_RES_4314_WL_PMU_PU |
			  BCMA_RES_4314_LDO3P3_PU |
			  BCMA_RES_4314_OTP_PU |
			  BCMA_RES_4314_WL_PWRSW_PU |
			  BCMA_RES_4314_LQ_AVAIL |
			  BCMA_RES_4314_LOGIC_RET |
			  BCMA_RES_4314_MEM_SLEEP |
			  BCMA_RES_4314_MACPHY_RET |
			  BCMA_RES_4314_WL_CORE_READY;
		max_msk = 0x3FFFFFFF;
		break;
	default:
		bcma_debug(bus, "PMU resource config unknown or not needed for device 0x%04X\n",
			   bus->chipinfo.id);
	}


	if (min_msk)
		bcma_cc_write32(cc, BCMA_CC_PMU_MINRES_MSK, min_msk);
	if (max_msk)
		bcma_cc_write32(cc, BCMA_CC_PMU_MAXRES_MSK, max_msk);


	mdelay(2);
}
