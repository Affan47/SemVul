psb_intel_sdvo_mode_fixup(struct drm_encoder *encoder,
				  const struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode)
{
	struct psb_intel_sdvo *psb_intel_sdvo = to_psb_intel_sdvo(encoder);
	int multiplier;


	if (psb_intel_sdvo->is_tv) {
		if (!psb_intel_sdvo_set_output_timings_from_mode(psb_intel_sdvo, mode))
			return false;

		(void) psb_intel_sdvo_set_input_timings_for_mode(psb_intel_sdvo,
							     mode,
							     adjusted_mode);
	} else if (psb_intel_sdvo->is_lvds) {
		if (!psb_intel_sdvo_set_output_timings_from_mode(psb_intel_sdvo,
							     psb_intel_sdvo->sdvo_lvds_fixed_mode))
			return false;

		(void) psb_intel_sdvo_set_input_timings_for_mode(psb_intel_sdvo,
							     mode,
							     adjusted_mode);
	}


	multiplier = psb_intel_sdvo_get_pixel_multiplier(adjusted_mode);
	psb_intel_mode_set_pixel_multiplier(adjusted_mode, multiplier);

	return true;
}
