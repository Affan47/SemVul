intel_disable_sdvo(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = encoder->base.dev->dev_private;
	struct intel_sdvo *intel_sdvo = to_sdvo(encoder);
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);
	u32 temp;

	intel_sdvo_set_active_outputs(intel_sdvo, 0);
	if (0)
		intel_sdvo_set_encoder_power_state(intel_sdvo,
						   DRM_MODE_DPMS_OFF);

	temp = I915_READ(intel_sdvo->sdvo_reg);

	temp &= ~SDVO_ENABLE;
	intel_sdvo_write_sdvox(intel_sdvo, temp);


	if (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B) {
		temp &= ~SDVO_PIPE_B_SELECT;
		temp |= SDVO_ENABLE;
		intel_sdvo_write_sdvox(intel_sdvo, temp);

		temp &= ~SDVO_ENABLE;
		intel_sdvo_write_sdvox(intel_sdvo, temp);
	}
}
