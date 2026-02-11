drm_dp_dual_mode_max_tmds_clock(enum drm_dp_dual_mode_type type,
				    struct i2c_adapter *adapter)
{
	uint8_t max_tmds_clock;
	ssize_t ret;


	if (type == DRM_DP_DUAL_MODE_NONE)
		return 0;


	if (type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		return 165000;

	ret = drm_dp_dual_mode_read(adapter, DP_DUAL_MODE_MAX_TMDS_CLOCK,
				    &max_tmds_clock, sizeof(max_tmds_clock));
	if (ret || max_tmds_clock == 0x00 || max_tmds_clock == 0xff) {
		DRM_DEBUG_KMS("Failed to query max TMDS clock\n");
		return 165000;
	}

	return max_tmds_clock * 5000 / 2;
}
