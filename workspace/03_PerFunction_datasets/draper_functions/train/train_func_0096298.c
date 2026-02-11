amdgpu_atombios_dp_get_adjust_train(const u8 link_status[DP_LINK_STATUS_SIZE],
						int lane_count,
						u8 train_set[4])
{
	u8 v = 0;
	u8 p = 0;
	int lane;

	for (lane = 0; lane < lane_count; lane++) {
		u8 this_v = drm_dp_get_adjust_request_voltage(link_status, lane);
		u8 this_p = drm_dp_get_adjust_request_pre_emphasis(link_status, lane);

		DRM_DEBUG_KMS("requested signal parameters: lane %d voltage %s pre_emph %s\n",
			  lane,
			  voltage_names[this_v >> DP_TRAIN_VOLTAGE_SWING_SHIFT],
			  pre_emph_names[this_p >> DP_TRAIN_PRE_EMPHASIS_SHIFT]);

		if (this_v > v)
			v = this_v;
		if (this_p > p)
			p = this_p;
	}

	if (v >= DP_VOLTAGE_MAX)
		v |= DP_TRAIN_MAX_SWING_REACHED;

	if (p >= DP_PRE_EMPHASIS_MAX)
		p |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

	DRM_DEBUG_KMS("using signal parameters: voltage %s pre_emph %s\n",
		  voltage_names[(v & DP_TRAIN_VOLTAGE_SWING_MASK) >> DP_TRAIN_VOLTAGE_SWING_SHIFT],
		  pre_emph_names[(p & DP_TRAIN_PRE_EMPHASIS_MASK) >> DP_TRAIN_PRE_EMPHASIS_SHIFT]);

	for (lane = 0; lane < 4; lane++)
		train_set[lane] = v | p;
}
