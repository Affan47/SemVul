intel_psr_write_vsc(struct intel_dp *intel_dp,
				const struct edp_vsc_psr *vsc_psr)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc = to_intel_crtc(dig_port->base.base.crtc);
	enum transcoder cpu_transcoder = crtc->config->cpu_transcoder;
	i915_reg_t ctl_reg = HSW_TVIDEO_DIP_CTL(cpu_transcoder);
	uint32_t *data = (uint32_t *) vsc_psr;
	unsigned int i;


	I915_WRITE(ctl_reg, 0);
	POSTING_READ(ctl_reg);

	for (i = 0; i < sizeof(*vsc_psr); i += 4) {
		I915_WRITE(HSW_TVIDEO_DIP_VSC_DATA(cpu_transcoder,
						   i >> 2), *data);
		data++;
	}
	for (; i < VIDEO_DIP_VSC_DATA_SIZE; i += 4)
		I915_WRITE(HSW_TVIDEO_DIP_VSC_DATA(cpu_transcoder,
						   i >> 2), 0);

	I915_WRITE(ctl_reg, VIDEO_DIP_ENABLE_VSC_HSW);
	POSTING_READ(ctl_reg);
}
