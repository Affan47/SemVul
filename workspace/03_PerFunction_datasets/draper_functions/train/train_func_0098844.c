tda998x_encoder_set_polling(struct tda998x_priv *priv,
					struct drm_connector *connector)
{
	if (priv->hdmi->irq)
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	else
		connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;
}
