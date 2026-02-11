cik_enable_sdma_mgls(struct amdgpu_device *adev,
				 bool enable)
{
	u32 orig, data;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS)) {
		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data |= 0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data |= 0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	} else {
		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data &= ~0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data &= ~0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	}
}
