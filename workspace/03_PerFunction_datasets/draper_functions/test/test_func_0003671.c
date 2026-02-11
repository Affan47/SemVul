drm_lspcon_set_mode(struct i2c_adapter *adapter,
			enum drm_lspcon_mode mode)
{
	u8 data = 0;
	int ret;
	int time_out = 200;
	enum drm_lspcon_mode current_mode;

	if (mode == DRM_LSPCON_MODE_PCON)
		data = DP_DUAL_MODE_LSPCON_MODE_PCON;


	ret = drm_dp_dual_mode_write(adapter, DP_DUAL_MODE_LSPCON_MODE_CHANGE,
				     &data, sizeof(data));
	if (ret < 0) {
		DRM_ERROR("LSPCON mode change failed\n");
		return ret;
	}


	do {
		ret = drm_lspcon_get_mode(adapter, &current_mode);
		if (ret) {
			DRM_ERROR("can't confirm LSPCON mode change\n");
			return ret;
		} else {
			if (current_mode != mode) {
				msleep(10);
				time_out -= 10;
			} else {
				DRM_DEBUG_KMS("LSPCON mode changed to %s\n",
						mode == DRM_LSPCON_MODE_LS ?
						"LS" : "PCON");
				return 0;
			}
		}
	} while (time_out);

	DRM_ERROR("LSPCON mode change timed out\n");
	return -ETIMEDOUT;
}
