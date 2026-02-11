gfx_v8_0_rlc_start(struct amdgpu_device *adev)
{
	u32 tmp = RREG32(mmRLC_CNTL);

	tmp = REG_SET_FIELD(tmp, RLC_CNTL, RLC_ENABLE_F32, 1);
	WREG32(mmRLC_CNTL, tmp);


	if (!(adev->flags & AMD_IS_APU))
		gfx_v8_0_enable_gui_idle_interrupt(adev, true);

	udelay(50);
}
