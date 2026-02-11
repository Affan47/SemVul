sdma_v3_0_enable(struct amdgpu_device *adev, bool enable)
{
	u32 f32_cntl;
	int i;

	if (enable == false) {
		sdma_v3_0_gfx_stop(adev);
		sdma_v3_0_rlc_stop(adev);
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntl = RREG32(mmSDMA0_F32_CNTL + sdma_offsets[i]);
		if (enable)
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 0);
		else
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 1);
		WREG32(mmSDMA0_F32_CNTL + sdma_offsets[i], f32_cntl);
	}
}
