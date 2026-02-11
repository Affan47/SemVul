intel_dp_set_link_train(struct intel_dp *intel_dp,
			uint32_t *DP,
			uint8_t dp_train_pat)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv =
		to_i915(intel_dig_port->base.base.dev);
	uint8_t buf[sizeof(intel_dp->train_set) + 1];
	int ret, len;

	_intel_dp_set_link_train(intel_dp, DP, dp_train_pat);

	I915_WRITE(intel_dp->output_reg, *DP);
	POSTING_READ(intel_dp->output_reg);

	buf[0] = dp_train_pat;
	if ((dp_train_pat & DP_TRAINING_PATTERN_MASK) ==
	    DP_TRAINING_PATTERN_DISABLE) {

		len = 1;
	} else {

		memcpy(buf + 1, intel_dp->train_set, intel_dp->lane_count);
		len = intel_dp->lane_count + 1;
	}

	ret = drm_dp_dpcd_write(&intel_dp->aux, DP_TRAINING_PATTERN_SET,
				buf, len);

	return ret == len;
}
