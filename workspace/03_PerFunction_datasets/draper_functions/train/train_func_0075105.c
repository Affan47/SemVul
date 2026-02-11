intel_psr_exit(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_dp *intel_dp = dev_priv->psr.enabled;
	struct drm_crtc *crtc = dp_to_dig_port(intel_dp)->base.base.crtc;
	enum pipe pipe = to_intel_crtc(crtc)->pipe;
	u32 val;

	if (!dev_priv->psr.active)
		return;

	if (HAS_DDI(dev)) {
		val = I915_READ(EDP_PSR_CTL(dev));

		WARN_ON(!(val & EDP_PSR_ENABLE));

		I915_WRITE(EDP_PSR_CTL(dev), val & ~EDP_PSR_ENABLE);
	} else {
		val = I915_READ(VLV_PSRCTL(pipe));


		val &= ~VLV_EDP_PSR_ACTIVE_ENTRY;
		I915_WRITE(VLV_PSRCTL(pipe), val);


		drm_dp_dpcd_writeb(&intel_dp->aux, DP_SET_POWER,
				   DP_SET_POWER_D0);
	}

	dev_priv->psr.active = false;
}
