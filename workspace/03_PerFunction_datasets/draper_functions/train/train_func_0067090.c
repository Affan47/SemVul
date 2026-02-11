gen9_enable_rc6(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *ring;
	uint32_t rc6_mask = 0;
	int unused;


	I915_WRITE(GEN6_RC_STATE, 0);


	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);


	I915_WRITE(GEN6_RC_CONTROL, 0);


	if (IS_SKYLAKE(dev))
		I915_WRITE(GEN6_RC6_WAKE_RATE_LIMIT, 108 << 16);
	else
		I915_WRITE(GEN6_RC6_WAKE_RATE_LIMIT, 54 << 16);
	I915_WRITE(GEN6_RC_EVALUATION_INTERVAL, 125000);
	I915_WRITE(GEN6_RC_IDLE_HYSTERSIS, 25);
	for_each_ring(ring, dev_priv, unused)
		I915_WRITE(RING_MAX_IDLE(ring->mmio_base), 10);

	if (HAS_GUC_UCODE(dev))
		I915_WRITE(GUC_MAX_IDLE_COUNT, 0xA);

	I915_WRITE(GEN6_RC_SLEEP, 0);


	I915_WRITE(GEN9_MEDIA_PG_IDLE_HYSTERESIS, 25);
	I915_WRITE(GEN9_RENDER_PG_IDLE_HYSTERESIS, 25);


	if (intel_enable_rc6(dev) & INTEL_RC6_ENABLE)
		rc6_mask = GEN6_RC_CTL_RC6_ENABLE;
	DRM_INFO("RC6 %s\n", (rc6_mask & GEN6_RC_CTL_RC6_ENABLE) ?
			"on" : "off");

	if ((IS_SKYLAKE(dev) && INTEL_REVID(dev) <= SKL_REVID_D0) ||
	    (IS_BROXTON(dev) && INTEL_REVID(dev) <= BXT_REVID_A0)) {
		I915_WRITE(GEN6_RC6_THRESHOLD, 625);
		I915_WRITE(GEN6_RC_CONTROL, GEN6_RC_CTL_HW_ENABLE |
			   GEN7_RC_CTL_TO_MODE |
			   rc6_mask);
	} else {
		I915_WRITE(GEN6_RC6_THRESHOLD, 37500);
		I915_WRITE(GEN6_RC_CONTROL, GEN6_RC_CTL_HW_ENABLE |
			   GEN6_RC_CTL_EI_MODE(1) |
			   rc6_mask);
	}


	if ((IS_BROXTON(dev) && (INTEL_REVID(dev) < BXT_REVID_B0)) ||
	    ((IS_SKL_GT3(dev) || IS_SKL_GT4(dev)) && (INTEL_REVID(dev) <= SKL_REVID_F0)))
		I915_WRITE(GEN9_PG_ENABLE, 0);
	else
		I915_WRITE(GEN9_PG_ENABLE, (rc6_mask & GEN6_RC_CTL_RC6_ENABLE) ?
				(GEN9_RENDER_PG_ENABLE | GEN9_MEDIA_PG_ENABLE) : 0);

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);

}
