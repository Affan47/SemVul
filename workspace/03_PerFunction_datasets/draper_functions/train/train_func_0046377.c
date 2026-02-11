vlv_resume_prepare(struct drm_i915_private *dev_priv,
				bool rpm_resume)
{
	struct drm_device *dev = dev_priv->dev;
	int err;
	int ret;


	ret = vlv_force_gfx_clock(dev_priv, true);

	if (!IS_CHERRYVIEW(dev_priv))
		vlv_restore_gunit_s0ix_state(dev_priv);

	err = vlv_allow_gt_wake(dev_priv, true);
	if (!ret)
		ret = err;

	err = vlv_force_gfx_clock(dev_priv, false);
	if (!ret)
		ret = err;

	vlv_check_no_gt_access(dev_priv);

	if (rpm_resume) {
		intel_init_clock_gating(dev);
		i915_gem_restore_fences(dev);
	}

	return ret;
}
