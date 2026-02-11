sil164_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct sil164_priv *priv = to_sil164_priv(encoder);
	bool on = (mode == DRM_MODE_DPMS_ON);
	bool duallink = (on && encoder->crtc->mode.clock > 165000);

	sil164_set_power_state(drm_i2c_encoder_get_client(encoder), on);

	if (priv->duallink_slave)
		sil164_set_power_state(priv->duallink_slave, duallink);
}
