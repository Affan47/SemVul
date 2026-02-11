edp_panel_off(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum intel_display_power_domain power_domain;
	u32 pp;
	u32 pp_ctrl_reg;

	lockdep_assert_held(&dev_priv->pps_mutex);

	if (!is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("Turn eDP port %c panel power off\n",
		      port_name(dp_to_dig_port(intel_dp)->port));

	WARN(!intel_dp->want_panel_vdd, "Need eDP port %c VDD to turn off panel\n",
	     port_name(dp_to_dig_port(intel_dp)->port));

	pp = ironlake_get_pp_control(intel_dp);


	pp &= ~(POWER_TARGET_ON | PANEL_POWER_RESET | EDP_FORCE_VDD |
		EDP_BLC_ENABLE);

	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);

	intel_dp->want_panel_vdd = false;

	I915_WRITE(pp_ctrl_reg, pp);
	POSTING_READ(pp_ctrl_reg);

	intel_dp->last_power_cycle = jiffies;
	wait_panel_off(intel_dp);


	power_domain = intel_display_port_aux_power_domain(intel_encoder);
	intel_display_power_put(dev_priv, power_domain);
}
