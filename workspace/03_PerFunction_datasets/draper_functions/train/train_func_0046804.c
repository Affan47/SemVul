chv_data_lane_soft_reset(struct intel_encoder *encoder,
				     bool reset)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum dpio_channel ch = vlv_dport_to_channel(enc_to_dig_port(&encoder->base));
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);
	enum pipe pipe = crtc->pipe;
	uint32_t val;

	val = vlv_dpio_read(dev_priv, pipe, VLV_PCS01_DW0(ch));
	if (reset)
		val &= ~(DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET);
	else
		val |= DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET;
	vlv_dpio_write(dev_priv, pipe, VLV_PCS01_DW0(ch), val);

	if (crtc->config->lane_count > 2) {
		val = vlv_dpio_read(dev_priv, pipe, VLV_PCS23_DW0(ch));
		if (reset)
			val &= ~(DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET);
		else
			val |= DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET;
		vlv_dpio_write(dev_priv, pipe, VLV_PCS23_DW0(ch), val);
	}

	val = vlv_dpio_read(dev_priv, pipe, VLV_PCS01_DW1(ch));
	val |= CHV_PCS_REQ_SOFTRESET_EN;
	if (reset)
		val &= ~DPIO_PCS_CLK_SOFT_RESET;
	else
		val |= DPIO_PCS_CLK_SOFT_RESET;
	vlv_dpio_write(dev_priv, pipe, VLV_PCS01_DW1(ch), val);

	if (crtc->config->lane_count > 2) {
		val = vlv_dpio_read(dev_priv, pipe, VLV_PCS23_DW1(ch));
		val |= CHV_PCS_REQ_SOFTRESET_EN;
		if (reset)
			val &= ~DPIO_PCS_CLK_SOFT_RESET;
		else
			val |= DPIO_PCS_CLK_SOFT_RESET;
		vlv_dpio_write(dev_priv, pipe, VLV_PCS23_DW1(ch), val);
	}
}
