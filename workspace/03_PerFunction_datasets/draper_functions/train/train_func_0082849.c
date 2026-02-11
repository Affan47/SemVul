amdgpu_connector_encoder_is_hbr2(struct drm_connector *connector)
{
	struct drm_encoder *encoder;
	struct amdgpu_encoder *amdgpu_encoder;
	int i;
	bool found = false;

	for (i = 0; i < DRM_CONNECTOR_MAX_ENCODER; i++) {
		if (connector->encoder_ids[i] == 0)
			break;
		encoder = drm_encoder_find(connector->dev,
					connector->encoder_ids[i]);
		if (!encoder)
			continue;

		amdgpu_encoder = to_amdgpu_encoder(encoder);
		if (amdgpu_encoder->caps & ATOM_ENCODER_CAP_RECORD_HBR2)
			found = true;
	}

	return found;
}
