intel_ddi_connector_get_hw_state(struct intel_connector *intel_connector)
{
	struct drm_device *dev = intel_connector->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_encoder *intel_encoder = intel_connector->encoder;
	int type = intel_connector->base.connector_type;
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	enum pipe pipe = 0;
	enum transcoder cpu_transcoder;
	enum intel_display_power_domain power_domain;
	uint32_t tmp;

	power_domain = intel_display_port_power_domain(intel_encoder);
	if (!intel_display_power_is_enabled(dev_priv, power_domain))
		return false;

	if (!intel_encoder->get_hw_state(intel_encoder, &pipe))
		return false;

	if (port == PORT_A)
		cpu_transcoder = TRANSCODER_EDP;
	else
		cpu_transcoder = (enum transcoder) pipe;

	tmp = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));

	switch (tmp & TRANS_DDI_MODE_SELECT_MASK) {
	case TRANS_DDI_MODE_SELECT_HDMI:
	case TRANS_DDI_MODE_SELECT_DVI:
		return (type == DRM_MODE_CONNECTOR_HDMIA);

	case TRANS_DDI_MODE_SELECT_DP_SST:
		if (type == DRM_MODE_CONNECTOR_eDP)
			return true;
		return (type == DRM_MODE_CONNECTOR_DisplayPort);
	case TRANS_DDI_MODE_SELECT_DP_MST:


		return false;

	case TRANS_DDI_MODE_SELECT_FDI:
		return (type == DRM_MODE_CONNECTOR_VGA);

	default:
		return false;
	}
}
