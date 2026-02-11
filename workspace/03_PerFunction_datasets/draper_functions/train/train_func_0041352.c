oaktrail_hdmi_dpms(struct drm_encoder *encoder, int mode)
{
	static int dpms_mode = -1;

	struct drm_device *dev = encoder->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	u32 temp;

	if (dpms_mode == mode)
		return;

	if (mode != DRM_MODE_DPMS_ON)
		temp = 0x0;
	else
		temp = 0x99;

	dpms_mode = mode;
	HDMI_WRITE(HDMI_VIDEO_REG, temp);
}
