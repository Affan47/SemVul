si_program_tp(struct radeon_device *rdev)
{
	int i;
	enum r600_td td = R600_TD_DFLT;

	for (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		WREG32(CG_FFCT_0 + (i * 4), (UTC_0(r600_utc[i]) | DTC_0(r600_dtc[i])));

	if (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	else
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);

	if (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);

	if (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
}
