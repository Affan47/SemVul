intel_dp_create_fake_mst_encoder(struct intel_digital_port *intel_dig_port, enum pipe pipe)
{
	struct intel_dp_mst_encoder *intel_mst;
	struct intel_encoder *intel_encoder;
	struct drm_device *dev = intel_dig_port->base.base.dev;

	intel_mst = kzalloc(sizeof(*intel_mst), GFP_KERNEL);

	if (!intel_mst)
		return NULL;

	intel_mst->pipe = pipe;
	intel_encoder = &intel_mst->base;
	intel_mst->primary = intel_dig_port;

	drm_encoder_init(dev, &intel_encoder->base, &intel_dp_mst_enc_funcs,
			 DRM_MODE_ENCODER_DPMST);

	intel_encoder->type = INTEL_OUTPUT_DP_MST;
	intel_encoder->crtc_mask = 0x7;
	intel_encoder->cloneable = 0;

	intel_encoder->compute_config = intel_dp_mst_compute_config;
	intel_encoder->disable = intel_mst_disable_dp;
	intel_encoder->post_disable = intel_mst_post_disable_dp;
	intel_encoder->pre_enable = intel_mst_pre_enable_dp;
	intel_encoder->enable = intel_mst_enable_dp;
	intel_encoder->get_hw_state = intel_dp_mst_enc_get_hw_state;
	intel_encoder->get_config = intel_dp_mst_enc_get_config;

	return intel_mst;

}
