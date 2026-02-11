gen9_sanitize_power_well_requests(struct drm_i915_private *dev_priv,
				  struct i915_power_well *power_well)
{
	enum skl_disp_power_wells power_well_id = power_well->data;
	u32 val;
	u32 mask;

	mask = SKL_POWER_WELL_REQ(power_well_id);

	val = I915_READ(HSW_PWR_WELL_KVMR);
	if (WARN_ONCE(val & mask, "Clearing unexpected KVMR request for %s\n",
		      power_well->name))
		I915_WRITE(HSW_PWR_WELL_KVMR, val & ~mask);

	val = I915_READ(HSW_PWR_WELL_BIOS);
	val |= I915_READ(HSW_PWR_WELL_DEBUG);

	if (!(val & mask))
		return;


	if (power_well_id == SKL_DISP_PW_1 ||
	    ((IS_SKYLAKE(dev_priv) || IS_KABYLAKE(dev_priv)) &&
	     power_well_id == SKL_DISP_PW_MISC_IO))
		DRM_DEBUG_DRIVER("Clearing auxiliary requests for %s forced on "
				 "by DMC\n", power_well->name);
	else
		WARN_ONCE(1, "Clearing unexpected auxiliary requests for %s\n",
			  power_well->name);

	I915_WRITE(HSW_PWR_WELL_BIOS, val & ~mask);
	I915_WRITE(HSW_PWR_WELL_DEBUG, val & ~mask);
}
