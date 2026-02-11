intel_uncore_arm_unclaimed_mmio_detection(struct drm_i915_private *dev_priv)
{
	if (unlikely(i915.mmio_debug ||
		     dev_priv->uncore.unclaimed_mmio_check <= 0))
		return false;

	if (unlikely(intel_uncore_unclaimed_mmio(dev_priv))) {
		DRM_DEBUG("Unclaimed register detected, "
			  "enabling oneshot unclaimed register reporting. "
			  "Please use i915.mmio_debug=N for more information.\n");
		i915.mmio_debug++;
		dev_priv->uncore.unclaimed_mmio_check--;
		return true;
	}

	return false;
}
