radeon_encoder_get_dp_bridge_encoder_id(struct drm_encoder *encoder)
{
	struct drm_encoder *other_encoder = radeon_get_external_encoder(encoder);

	if (other_encoder) {
		struct radeon_encoder *radeon_encoder = to_radeon_encoder(other_encoder);

		switch (radeon_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_TRAVIS:
		case ENCODER_OBJECT_ID_NUTMEG:
			return radeon_encoder->encoder_id;
		default:
			return ENCODER_OBJECT_ID_NONE;
		}
	}
	return ENCODER_OBJECT_ID_NONE;
}
