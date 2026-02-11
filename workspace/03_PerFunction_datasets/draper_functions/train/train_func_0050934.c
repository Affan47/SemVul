vlv_allow_gt_wake(struct drm_i915_private *dev_priv, bool allow)
{
	u32 val;
	int err = 0;

	val = I915_READ(VLV_GTLC_WAKE_CTRL);
	val &= ~VLV_GTLC_ALLOWWAKEREQ;
	if (allow)
		val |= VLV_GTLC_ALLOWWAKEREQ;
	I915_WRITE(VLV_GTLC_WAKE_CTRL, val);
	POSTING_READ(VLV_GTLC_WAKE_CTRL);

#define COND (!!(I915_READ(VLV_GTLC_PW_STATUS) & VLV_GTLC_ALLOWWAKEACK) == \
	      allow)
	err = wait_for(COND, 1);
	if (err)
		DRM_ERROR("timeout disabling GT waking\n");
	return err;
#undef COND
}
