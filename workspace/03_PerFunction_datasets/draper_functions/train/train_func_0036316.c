sumo_set_forced_mode_enabled(struct radeon_device *rdev)
{
	int i;

	sumo_set_forced_mode(rdev, true);
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(CG_SCLK_STATUS) & SCLK_OVERCLK_DETECT)
			break;
		udelay(1);
	}
}
