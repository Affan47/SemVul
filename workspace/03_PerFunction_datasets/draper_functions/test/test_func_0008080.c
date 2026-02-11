vlv_signal_levels(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_digital_port *dport = dp_to_dig_port(intel_dp);
	struct intel_crtc *intel_crtc =
		to_intel_crtc(dport->base.base.crtc);
	unsigned long demph_reg_value, preemph_reg_value,
		uniqtranscale_reg_value;
	uint8_t train_set = intel_dp->train_set[0];
	enum dpio_channel port = vlv_dport_to_channel(dport);
	int pipe = intel_crtc->pipe;

	switch (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) {
	case DP_TRAIN_PRE_EMPH_LEVEL_0:
		preemph_reg_value = 0x0004000;
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B405555;
			uniqtranscale_reg_value = 0x552AB83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x5548B83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			demph_reg_value = 0x2B245555;
			uniqtranscale_reg_value = 0x5560B83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
			demph_reg_value = 0x2B405555;
			uniqtranscale_reg_value = 0x5598DA3A;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_1:
		preemph_reg_value = 0x0002000;
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x5552B83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B404848;
			uniqtranscale_reg_value = 0x5580B83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x55ADDA3A;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_2:
		preemph_reg_value = 0x0000000;
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B305555;
			uniqtranscale_reg_value = 0x5570B83A;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B2B4040;
			uniqtranscale_reg_value = 0x55ADDA3A;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_3:
		preemph_reg_value = 0x0006000;
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x1B405555;
			uniqtranscale_reg_value = 0x55ADDA3A;
			break;
		default:
			return 0;
		}
		break;
	default:
		return 0;
	}

	mutex_lock(&dev_priv->sb_lock);
	vlv_dpio_write(dev_priv, pipe, VLV_TX_DW5(port), 0x00000000);
	vlv_dpio_write(dev_priv, pipe, VLV_TX_DW4(port), demph_reg_value);
	vlv_dpio_write(dev_priv, pipe, VLV_TX_DW2(port),
			 uniqtranscale_reg_value);
	vlv_dpio_write(dev_priv, pipe, VLV_TX_DW3(port), 0x0C782040);
	vlv_dpio_write(dev_priv, pipe, VLV_PCS_DW11(port), 0x00030000);
	vlv_dpio_write(dev_priv, pipe, VLV_PCS_DW9(port), preemph_reg_value);
	vlv_dpio_write(dev_priv, pipe, VLV_TX_DW5(port), 0x80000000);
	mutex_unlock(&dev_priv->sb_lock);

	return 0;
}
