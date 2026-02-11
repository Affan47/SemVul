vlv_setup_backlight(struct intel_connector *connector, enum pipe pipe)
{
	struct drm_device *dev = connector->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_panel *panel = &connector->panel;
	u32 ctl, ctl2, val;

	if (WARN_ON(pipe != PIPE_A && pipe != PIPE_B))
		return -ENODEV;

	ctl2 = I915_READ(VLV_BLC_PWM_CTL2(pipe));
	panel->backlight.active_low_pwm = ctl2 & BLM_POLARITY_I965;

	ctl = I915_READ(VLV_BLC_PWM_CTL(pipe));
	panel->backlight.max = ctl >> 16;

	if (!panel->backlight.max)
		panel->backlight.max = get_backlight_max_vbt(connector);

	if (!panel->backlight.max)
		return -ENODEV;

	panel->backlight.min = get_backlight_min_vbt(connector);

	val = _vlv_get_backlight(dev, pipe);
	panel->backlight.level = intel_panel_compute_brightness(connector, val);

	panel->backlight.enabled = (ctl2 & BLM_PWM_ENABLE) &&
		panel->backlight.level != 0;

	return 0;
}
