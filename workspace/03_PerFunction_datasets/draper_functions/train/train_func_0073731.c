radeon_hdmi_set_color_depth(struct drm_encoder *encoder)
{
	int bpc = 8;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	if (!dig || !dig->afmt)
		return;

	if (encoder->crtc) {
		struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
		bpc = radeon_crtc->bpc;
	}

	if (radeon_encoder->audio && radeon_encoder->audio->set_color_depth)
		radeon_encoder->audio->set_color_depth(encoder, dig->afmt->offset, bpc);
}
