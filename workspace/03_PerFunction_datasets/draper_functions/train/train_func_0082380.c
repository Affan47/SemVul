intel_ddi_pll_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t val = I915_READ(LCPLL_CTL);

	if (IS_SKYLAKE(dev) || IS_KABYLAKE(dev)) {
		int cdclk_freq;

		cdclk_freq = dev_priv->display.get_display_clock_speed(dev);
		dev_priv->skl_boot_cdclk = cdclk_freq;
		if (skl_sanitize_cdclk(dev_priv))
			DRM_DEBUG_KMS("Sanitized cdclk programmed by pre-os\n");
		if (!(I915_READ(LCPLL1_CTL) & LCPLL_PLL_ENABLE))
			DRM_ERROR("LCPLL1 is disabled\n");
	} else if (!IS_BROXTON(dev_priv)) {


		if (val & LCPLL_CD_SOURCE_FCLK)
			DRM_ERROR("CDCLK source is not LCPLL\n");

		if (val & LCPLL_PLL_DISABLE)
			DRM_ERROR("LCPLL is disabled\n");
	}
}
