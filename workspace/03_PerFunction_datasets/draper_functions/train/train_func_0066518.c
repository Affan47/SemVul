intel_init_clock_gating_hooks(struct drm_i915_private *dev_priv)
{
	if (IS_SKYLAKE(dev_priv))
		dev_priv->display.init_clock_gating = skylake_init_clock_gating;
	else if (IS_KABYLAKE(dev_priv))
		dev_priv->display.init_clock_gating = kabylake_init_clock_gating;
	else if (IS_BROXTON(dev_priv))
		dev_priv->display.init_clock_gating = bxt_init_clock_gating;
	else if (IS_BROADWELL(dev_priv))
		dev_priv->display.init_clock_gating = broadwell_init_clock_gating;
	else if (IS_CHERRYVIEW(dev_priv))
		dev_priv->display.init_clock_gating = cherryview_init_clock_gating;
	else if (IS_HASWELL(dev_priv))
		dev_priv->display.init_clock_gating = haswell_init_clock_gating;
	else if (IS_IVYBRIDGE(dev_priv))
		dev_priv->display.init_clock_gating = ivybridge_init_clock_gating;
	else if (IS_VALLEYVIEW(dev_priv))
		dev_priv->display.init_clock_gating = valleyview_init_clock_gating;
	else if (IS_GEN6(dev_priv))
		dev_priv->display.init_clock_gating = gen6_init_clock_gating;
	else if (IS_GEN5(dev_priv))
		dev_priv->display.init_clock_gating = ironlake_init_clock_gating;
	else if (IS_G4X(dev_priv))
		dev_priv->display.init_clock_gating = g4x_init_clock_gating;
	else if (IS_CRESTLINE(dev_priv))
		dev_priv->display.init_clock_gating = crestline_init_clock_gating;
	else if (IS_BROADWATER(dev_priv))
		dev_priv->display.init_clock_gating = broadwater_init_clock_gating;
	else if (IS_GEN3(dev_priv))
		dev_priv->display.init_clock_gating = gen3_init_clock_gating;
	else if (IS_I85X(dev_priv) || IS_I865G(dev_priv))
		dev_priv->display.init_clock_gating = i85x_init_clock_gating;
	else if (IS_GEN2(dev_priv))
		dev_priv->display.init_clock_gating = i830_init_clock_gating;
	else {
		MISSING_CASE(INTEL_DEVID(dev_priv));
		dev_priv->display.init_clock_gating = nop_init_clock_gating;
	}
}
