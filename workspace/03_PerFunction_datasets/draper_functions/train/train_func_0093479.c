si_halt_rlc(struct radeon_device *rdev)
{
	u32 data, orig;

	orig = data = RREG32(RLC_CNTL);

	if (data & RLC_ENABLE) {
		data &= ~RLC_ENABLE;
		WREG32(RLC_CNTL, data);

		si_wait_for_rlc_serdes(rdev);
	}

	return orig;
}
