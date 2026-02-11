vlv_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	struct drm_device *dev = connector->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int clock;

	if ((I915_READ(CBR1_VLV) & CBR_PWM_CLOCK_MUX_SELECT) == 0) {
		if (IS_CHERRYVIEW(dev))
			return KHz(19200) / (pwm_freq_hz * 16);
		else
			return MHz(25) / (pwm_freq_hz * 16);
	} else {
		clock = intel_hrawclk(dev);
		return MHz(clock) / (pwm_freq_hz * 128);
	}
}
