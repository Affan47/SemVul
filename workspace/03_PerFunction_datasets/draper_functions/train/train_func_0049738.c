vlv_is_psr_active_on_pipe(struct drm_device *dev, int pipe)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t val;

	val = I915_READ(VLV_PSRSTAT(pipe)) &
	      VLV_EDP_PSR_CURR_STATE_MASK;
	return (val == VLV_EDP_PSR_ACTIVE_NORFB_UP) ||
	       (val == VLV_EDP_PSR_ACTIVE_SF_UPDATE);
}
