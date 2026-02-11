radeon_legacy_tv_adjust_pll1(struct drm_encoder *encoder,
				  uint32_t *htotal_cntl, uint32_t *ppll_ref_div,
				  uint32_t *ppll_div_3, uint32_t *pixclks_cntl)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	const struct radeon_tv_mode_constants *const_ptr;

	const_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, NULL);
	if (!const_ptr)
		return;

	*htotal_cntl = (const_ptr->hor_total & 0x7) | RADEON_HTOT_CNTL_VGA_EN;

	*ppll_ref_div = const_ptr->crtcPLL_M;

	*ppll_div_3 = (const_ptr->crtcPLL_N & 0x7ff) | (get_post_div(const_ptr->crtcPLL_post_div) << 16);
	*pixclks_cntl &= ~(RADEON_PIX2CLK_SRC_SEL_MASK | RADEON_PIXCLK_TV_SRC_SEL);
	*pixclks_cntl |= RADEON_PIX2CLK_SRC_SEL_P2PLLCLK;
}
