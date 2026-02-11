auth_cb(DBusError *derr, void *user_data)
{
	struct audio_device *dev = user_data;
	struct dev_priv *priv = dev->priv;

	if (derr == NULL)
		priv->authorized = TRUE;

	while (priv->auths) {
		struct service_auth *auth = priv->auths->data;

		auth->cb(derr, auth->user_data);
		priv->auths = g_slist_remove(priv->auths, auth);
		g_free(auth);
	}
}
