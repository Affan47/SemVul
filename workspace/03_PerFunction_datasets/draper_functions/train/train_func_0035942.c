vlv_hz_to_pwm(struct intel_connector *connector, u32 pwm_freq_hz)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	int mul, clock;

	if ((I915_READ(CBR1_VLV) & CBR_PWM_CLOCK_MUX_SELECT) == 0) {
		if (IS_CHERRYVIEW(dev_priv))
			clock = KHz(19200);
		else
			clock = MHz(25);
		mul = 16;
	} else {
		clock = KHz(dev_priv->rawclk_freq);
		mul = 128;
	}

	return DIV_ROUND_CLOSEST(clock, pwm_freq_hz * mul);
}
