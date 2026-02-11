i9xx_load_luts_internal(struct drm_crtc *crtc,
				    struct drm_property_blob *blob)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	enum pipe pipe = intel_crtc->pipe;
	int i;

	if (HAS_GMCH_DISPLAY(dev)) {
		if (intel_crtc->config->has_dsi_encoder)
			assert_dsi_pll_enabled(dev_priv);
		else
			assert_pll_enabled(dev_priv, pipe);
	}

	if (blob) {
		struct drm_color_lut *lut = (struct drm_color_lut *) blob->data;
		for (i = 0; i < 256; i++) {
			uint32_t word =
				(drm_color_lut_extract(lut[i].red, 8) << 16) |
				(drm_color_lut_extract(lut[i].green, 8) << 8) |
				drm_color_lut_extract(lut[i].blue, 8);

			if (HAS_GMCH_DISPLAY(dev))
				I915_WRITE(PALETTE(pipe, i), word);
			else
				I915_WRITE(LGC_PALETTE(pipe, i), word);
		}
	} else {
		for (i = 0; i < 256; i++) {
			uint32_t word = (i << 16) | (i << 8) | i;

			if (HAS_GMCH_DISPLAY(dev))
				I915_WRITE(PALETTE(pipe, i), word);
			else
				I915_WRITE(LGC_PALETTE(pipe, i), word);
		}
	}
}
