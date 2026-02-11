si_enable_dma_mgcg(struct radeon_device *rdev,
			       bool enable)
{
	u32 orig, data, offset;
	int i;

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_SDMA_MGCG)) {
		for (i = 0; i < 2; i++) {
			if (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			else
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data &= ~MEM_POWER_OVERRIDE;
			if (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);
			WREG32(DMA_CLK_CTRL + offset, 0x00000100);
		}
	} else {
		for (i = 0; i < 2; i++) {
			if (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			else
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data |= MEM_POWER_OVERRIDE;
			if (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);

			orig = data = RREG32(DMA_CLK_CTRL + offset);
			data = 0xff000000;
			if (data != orig)
				WREG32(DMA_CLK_CTRL + offset, data);
		}
	}
}
