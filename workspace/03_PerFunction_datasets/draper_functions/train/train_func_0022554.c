cik_enable_gui_idle_interrupt(struct radeon_device *rdev,
					  bool enable)
{
	u32 tmp = RREG32(CP_INT_CNTL_RING0);

	if (enable)
		tmp |= (CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	else
		tmp &= ~(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, tmp);
}
