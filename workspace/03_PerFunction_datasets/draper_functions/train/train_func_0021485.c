ch7006_encoder_get_modes(struct drm_encoder *encoder,
				    struct drm_connector *connector)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	const struct ch7006_mode *mode;
	int n = 0;

	for (mode = ch7006_modes; mode->mode.clock; mode++) {
		if (~mode->valid_scales & 1<<priv->scale ||
		    ~mode->valid_norms & 1<<priv->norm)
			continue;

		drm_mode_probed_add(connector,
				drm_mode_duplicate(encoder->dev, &mode->mode));

		n++;
	}

	return n;
}
