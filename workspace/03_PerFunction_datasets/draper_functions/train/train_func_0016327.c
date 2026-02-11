r100_hpd_sense(struct radeon_device *rdev, enum radeon_hpd_id hpd)
{
	bool connected = false;

	switch (hpd) {
	case RADEON_HPD_1:
		if (RREG32(RADEON_FP_GEN_CNTL) & RADEON_FP_DETECT_SENSE)
			connected = true;
		break;
	case RADEON_HPD_2:
		if (RREG32(RADEON_FP2_GEN_CNTL) & RADEON_FP2_DETECT_SENSE)
			connected = true;
		break;
	default:
		break;
	}
	return connected;
}
