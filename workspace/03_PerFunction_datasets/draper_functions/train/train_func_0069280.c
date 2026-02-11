cdv_intel_edp_backlight_off (struct gma_encoder *intel_encoder)
{
	struct drm_device *dev = intel_encoder->base.dev;
	struct cdv_intel_dp *intel_dp = intel_encoder->dev_priv;
	u32 pp;

	DRM_DEBUG_KMS("\n");
	gma_backlight_disable(dev);
	msleep(10);
	pp = REG_READ(PP_CONTROL);

	pp &= ~EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	msleep(intel_dp->backlight_off_delay);
}
