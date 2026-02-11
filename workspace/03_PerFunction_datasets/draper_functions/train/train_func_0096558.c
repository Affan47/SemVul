i9xx_setup_backlight(struct intel_connector *connector, enum pipe unused)
{
	struct drm_device *dev = connector->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_panel *panel = &connector->panel;
	u32 ctl, val;

	ctl = I915_READ(BLC_PWM_CTL);

	if (IS_GEN2(dev) || IS_I915GM(dev) || IS_I945GM(dev))
		panel->backlight.combination_mode = ctl & BLM_LEGACY_MODE;

	if (IS_PINEVIEW(dev))
		panel->backlight.active_low_pwm = ctl & BLM_POLARITY_PNV;

	panel->backlight.max = ctl >> 17;

	if (!panel->backlight.max) {
		panel->backlight.max = get_backlight_max_vbt(connector);
		panel->backlight.max >>= 1;
	}

	if (!panel->backlight.max)
		return -ENODEV;

	if (panel->backlight.combination_mode)
		panel->backlight.max *= 0xff;

	panel->backlight.min = get_backlight_min_vbt(connector);

	val = i9xx_get_backlight(connector);
	panel->backlight.level = intel_panel_compute_brightness(connector, val);

	panel->backlight.enabled = panel->backlight.level != 0;

	return 0;
}
