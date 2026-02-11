gfx_v7_0_update_rlc(struct amdgpu_device *adev, u32 rlc)
{
	u32 tmp;

	tmp = RREG32(mmRLC_CNTL);
	if (tmp != rlc)
		WREG32(mmRLC_CNTL, rlc);
}
