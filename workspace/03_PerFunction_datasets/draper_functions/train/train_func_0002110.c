r600_pcie_gart_tlb_flush(struct radeon_device *rdev)
{
	unsigned i;
	u32 tmp;


	if ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_RV740) &&
	    !(rdev->flags & RADEON_IS_AGP)) {
		void __iomem *ptr = (void *)rdev->gart.ptr;
		u32 tmp;


		WREG32(HDP_DEBUG1, 0);
		tmp = readl((void __iomem *)ptr);
	} else
		WREG32(R_005480_HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	WREG32(VM_CONTEXT0_INVALIDATION_LOW_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_INVALIDATION_HIGH_ADDR, (rdev->mc.gtt_end - 1) >> 12);
	WREG32(VM_CONTEXT0_REQUEST_RESPONSE, REQUEST_TYPE(1));
	for (i = 0; i < rdev->usec_timeout; i++) {

		tmp = RREG32(VM_CONTEXT0_REQUEST_RESPONSE);
		tmp = (tmp & RESPONSE_TYPE_MASK) >> RESPONSE_TYPE_SHIFT;
		if (tmp == 2) {
			printk(KERN_WARNING "[drm] r600 flush TLB failed\n");
			return;
		}
		if (tmp) {
			return;
		}
		udelay(1);
	}
}
