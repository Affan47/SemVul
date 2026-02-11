vlv_init_gpll_ref_freq(struct drm_i915_private *dev_priv)
{
	dev_priv->rps.gpll_ref_freq =
		vlv_get_cck_clock(dev_priv, "GPLL ref",
				  CCK_GPLL_CLOCK_CONTROL,
				  dev_priv->czclk_freq);

	DRM_DEBUG_DRIVER("GPLL reference freq: %d kHz\n",
			 dev_priv->rps.gpll_ref_freq);
}
