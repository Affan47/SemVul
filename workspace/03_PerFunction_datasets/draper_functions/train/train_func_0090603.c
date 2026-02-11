rs780_set_engine_clock_spc(struct radeon_device *rdev,
				       struct radeon_ps *new_ps,
				       struct radeon_ps *old_ps)
{
	struct igp_ps *new_state = rs780_get_ps(new_ps);
	struct igp_ps *old_state = rs780_get_ps(old_ps);
	struct igp_power_info *pi = rs780_get_pi(rdev);

	if ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		return;

	if (pi->crtc_id == 0)
		WREG32_P(CG_INTGFX_MISC, 0, ~FVTHROT_VBLANK_SEL);
	else
		WREG32_P(CG_INTGFX_MISC, FVTHROT_VBLANK_SEL, ~FVTHROT_VBLANK_SEL);

}
