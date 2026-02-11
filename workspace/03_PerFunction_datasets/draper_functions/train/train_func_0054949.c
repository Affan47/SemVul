determine_memory_type(struct amd64_pvt *pvt)
{
	u32 dram_ctrl, dcsm;

	switch (pvt->fam) {
	case 0xf:
		if (pvt->ext_model >= K8_REV_F)
			goto ddr3;

		pvt->dram_type = (pvt->dclr0 & BIT(18)) ? MEM_DDR : MEM_RDDR;
		return;

	case 0x10:
		if (pvt->dchr0 & DDR3_MODE)
			goto ddr3;

		pvt->dram_type = (pvt->dclr0 & BIT(16)) ? MEM_DDR2 : MEM_RDDR2;
		return;

	case 0x15:
		if (pvt->model < 0x60)
			goto ddr3;


		amd64_read_dct_pci_cfg(pvt, 0, DRAM_CONTROL, &dram_ctrl);
		dcsm = pvt->csels[0].csmasks[0];

		if (((dram_ctrl >> 8) & 0x7) == 0x2)
			pvt->dram_type = MEM_DDR4;
		else if (pvt->dclr0 & BIT(16))
			pvt->dram_type = MEM_DDR3;
		else if (dcsm & 0x3)
			pvt->dram_type = MEM_LRDDR3;
		else
			pvt->dram_type = MEM_RDDR3;

		return;

	case 0x16:
		goto ddr3;

	default:
		WARN(1, KERN_ERR "%s: Family??? 0x%x\n", __func__, pvt->fam);
		pvt->dram_type = MEM_EMPTY;
	}
	return;

ddr3:
	pvt->dram_type = (pvt->dclr0 & BIT(16)) ? MEM_DDR3 : MEM_RDDR3;
}
