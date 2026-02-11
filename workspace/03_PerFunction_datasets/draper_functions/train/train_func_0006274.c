radeon_best_single_encoder(struct drm_connector *connector)
{
	int enc_id = connector->encoder_ids[0];

	if (enc_id)
		return drm_encoder_find(connector->dev, enc_id);
	return NULL;
}
