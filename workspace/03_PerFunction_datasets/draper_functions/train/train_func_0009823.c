g4x_infoframe_enabled(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(encoder);
	u32 val = I915_READ(VIDEO_DIP_CTL);

	if ((val & VIDEO_DIP_ENABLE) == 0)
		return false;

	if ((val & VIDEO_DIP_PORT_MASK) != VIDEO_DIP_PORT(intel_dig_port->port))
		return false;

	return val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_SPD);
}
