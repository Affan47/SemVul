rv6xx_get_temp(struct radeon_device *rdev)
{
	u32 temp = (RREG32(CG_THERMAL_STATUS) & ASIC_T_MASK) >>
		ASIC_T_SHIFT;
	int actual_temp = temp & 0xff;

	if (temp & 0x100)
		actual_temp -= 256;

	return actual_temp * 1000;
}
