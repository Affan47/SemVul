intel_ddi_clock_get(struct intel_encoder *encoder,
			 struct intel_crtc_state *pipe_config)
{
	struct drm_device *dev = encoder->base.dev;

	if (INTEL_INFO(dev)->gen <= 8)
		hsw_ddi_clock_get(encoder, pipe_config);
	else if (IS_SKYLAKE(dev))
		skl_ddi_clock_get(encoder, pipe_config);
	else if (IS_BROXTON(dev))
		bxt_ddi_clock_get(encoder, pipe_config);
}
