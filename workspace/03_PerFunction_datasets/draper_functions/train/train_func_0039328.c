bcma_sprom_onchip_offset(struct bcma_bus *bus)
{
	struct bcma_device *cc = bus->drv_cc.core;
	u32 offset;


	if ((bcma_read32(cc, BCMA_CC_OTPS) & BCMA_CC_OTPS_GU_PROG_HW) == 0)
		return 0;


	offset = (bcma_read32(cc, BCMA_CC_OTPL) & BCMA_CC_OTPL_GURGN_OFFSET);
	return BCMA_CC_SPROM + (offset >> 3);
}
