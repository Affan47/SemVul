radeon_mst_encoder_prepare(struct drm_encoder *encoder)
{
	struct radeon_connector *radeon_connector;
	struct radeon_encoder *radeon_encoder, *primary;
	struct radeon_encoder_mst *mst_enc;
	struct radeon_encoder_atom_dig *dig_enc;

	radeon_connector = radeon_mst_find_connector(encoder);
	if (!radeon_connector) {
		DRM_DEBUG_KMS("failed to find connector %p\n", encoder);
		return;
	}
	radeon_encoder = to_radeon_encoder(encoder);

	radeon_mst_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	mst_enc = radeon_encoder->enc_priv;

	primary = mst_enc->primary;

	dig_enc = primary->enc_priv;

	mst_enc->port = radeon_connector->port;

	if (dig_enc->dig_encoder == -1) {
		dig_enc->dig_encoder = radeon_atom_pick_dig_encoder(&primary->base, -1);
		primary->offset = radeon_atom_set_enc_offset(dig_enc->dig_encoder);
		atombios_set_mst_encoder_crtc_source(encoder, dig_enc->dig_encoder);


	}
	DRM_DEBUG_KMS("%d %d\n", dig_enc->dig_encoder, primary->offset);
}
