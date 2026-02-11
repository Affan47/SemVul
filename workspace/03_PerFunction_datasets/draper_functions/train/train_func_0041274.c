edp_notify_handler(struct notifier_block *this, unsigned long code,
			      void *unused)
{
	struct intel_dp *intel_dp = container_of(this, typeof(* intel_dp),
						 edp_notifier);
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!is_edp(intel_dp) || code != SYS_RESTART)
		return 0;

	pps_lock(intel_dp);

	if (IS_VALLEYVIEW(dev)) {
		enum pipe pipe = vlv_power_sequencer_pipe(intel_dp);
		u32 pp_ctrl_reg, pp_div_reg;
		u32 pp_div;

		pp_ctrl_reg = VLV_PIPE_PP_CONTROL(pipe);
		pp_div_reg  = VLV_PIPE_PP_DIVISOR(pipe);
		pp_div = I915_READ(pp_div_reg);
		pp_div &= PP_REFERENCE_DIVIDER_MASK;


		I915_WRITE(pp_div_reg, pp_div | 0x1F);
		I915_WRITE(pp_ctrl_reg, PANEL_UNLOCK_REGS | PANEL_POWER_OFF);
		msleep(intel_dp->panel_power_cycle_delay);
	}

	pps_unlock(intel_dp);

	return 0;
}
