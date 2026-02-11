ch7006_lookup_mode(struct drm_encoder *encoder,
					     const struct drm_display_mode *drm_mode)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	const struct ch7006_mode *mode;

	for (mode = ch7006_modes; mode->mode.clock; mode++) {

		if (~mode->valid_norms & 1<<priv->norm)
			continue;

		if (mode->mode.hdisplay != drm_mode->hdisplay ||
		    mode->mode.vdisplay != drm_mode->vdisplay ||
		    mode->mode.vtotal != drm_mode->vtotal ||
		    mode->mode.htotal != drm_mode->htotal ||
		    mode->mode.clock != drm_mode->clock)
			continue;

		return mode;
	}

	return NULL;
}
