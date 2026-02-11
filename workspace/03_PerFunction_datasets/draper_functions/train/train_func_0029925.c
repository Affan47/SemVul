apic_set_eoi_write(void (*eoi_write)(u32 reg, u32 v))
{
	struct apic **drv;

	for (drv = __apicdrivers; drv < __apicdrivers_end; drv++) {

		WARN_ON((*drv)->eoi_write == eoi_write);
		(*drv)->eoi_write = eoi_write;
	}
}
