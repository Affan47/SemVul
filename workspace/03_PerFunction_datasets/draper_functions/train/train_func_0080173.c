lpt_disable_backlight(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	u32 tmp;

	intel_panel_actually_set_backlight(connector, 0);


	tmp = I915_READ(BLC_PWM_CPU_CTL2);
	if (tmp & BLM_PWM_ENABLE) {
		DRM_DEBUG_KMS("cpu backlight was enabled, disabling\n");
		I915_WRITE(BLC_PWM_CPU_CTL2, tmp & ~BLM_PWM_ENABLE);
	}

	tmp = I915_READ(BLC_PWM_PCH_CTL1);
	I915_WRITE(BLC_PWM_PCH_CTL1, tmp & ~BLM_PCH_PWM_ENABLE);
}
